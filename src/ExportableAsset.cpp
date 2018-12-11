#include "externals.h"
#include "ExportableAsset.h"
#include "AccessorPacker.h"
#include "Arguments.h"
#include "progress.h"
#include "timeControl.h"
#include "version.h"
#include "picosha2.h"
#include "milo.h"

using GLTF::Constants::WebGL;

struct MStringComparer
{
    bool operator ()(const MString& a, const MString& b) const
    {
        return strcmp(a.asChar(), b.asChar()) < 0;
    }
};

ExportableAsset::ExportableAsset(const Arguments& args)
    : m_resources{ args }
    , m_scene{ m_resources }
{
    m_glAsset.scenes.push_back(&m_scene.glScene);
    m_glAsset.scene = 0;

    m_glAsset.metadata = &m_glMetadata;
    m_glMetadata.generator = std::string("Maya2glTF ") + version;
    m_glMetadata.version = "2.0";
    m_glMetadata.copyright = args.copyright.asChar();

    if (args.dumpMaya)
    {
        *args.dumpMaya << "{" << indent << endl;
    }

    // Delete the folder before saving:
    // (1) this is async on NTFS, so deleting it first allows overlap with the export.
    // (2) if anything goes wrong, we don't want the user to think the export succeeded.
    const auto sceneName = std::string(args.sceneName.asChar());
    const auto outputFolder = path(args.outputFolder.asChar());
    if (args.cleanOutputFolder && exists(outputFolder))
    {
        std::cout << prefix << "Deleting " << outputFolder << "..." << endl;
        remove_all(outputFolder);
    }

    const auto currentFrameTime = MAnimControl::currentTime();

    setCurrentTime(args.initialValuesTime, args.redrawViewport);

    size_t progressStepCount = args.selection.size();

    for (auto& clipArg : args.animationClips)
    {
        progressStepCount += clipArg.frameCount() / checkProgressFrameInterval;
    }

    uiSetupProgress(progressStepCount);

    for (auto& dagPath : args.selection)
    {
        uiAdvanceProgress(std::string("exporting mesh ") + dagPath.partialPathName().asChar());
        cout << prefix << "Processing '" << dagPath.partialPathName().asChar() << "' ..." << endl;
        m_scene.getNode(dagPath);
    }

    if (!args.keepShapeNodes)
    {
        m_scene.mergeRedundantShapeNodes();
    }

    // Now export animation clips of all the nodes, in one pass over the slow timeline
    const auto clipCount = args.animationClips.size();

    if (clipCount)
    {
        for (auto& clipArg : args.animationClips)
        {
            uiAdvanceProgress("exporting clip " + clipArg.name);
            auto clip = std::make_unique<ExportableClip>(args, clipArg, m_scene);
            if (!clip->glAnimation.channels.empty())
            {
                m_glAsset.animations.push_back(&clip->glAnimation);
                m_clips.emplace_back(std::move(clip));
            }
        }
    }
    else if (currentFrameTime != args.initialValuesTime)
    {
        // When we export just a single frame, we normally bake the geometry at that frame.
        // However, when explicitly specifying a different initialValuesTime argument, we bake the values at the initial frame,
        // and re-evaluate the node-transforms and blend-shape-weights of the current frame, not the initial-values frame.
        setCurrentTime(currentFrameTime, args.redrawViewport);
        m_scene.updateCurrentValues();
    }

    const auto rootScaleFactor = args.getRootScaleFactor();
    if (args.forceRootNode || rootScaleFactor != 1)
    {
        // Create global root node for scaling.
        m_scene.glScene.nodes.push_back(&m_glRootNode);

        if (rootScaleFactor != 1)
        {
            auto& trs = m_glRootTransform;
            m_glRootNode.transform = &trs;
            makeIdentity(trs);
            trs.scale[0] = trs.scale[1] = trs.scale[2] = rootScaleFactor;
        }

        for (auto* node : m_scene.orphans())
        {
            m_glRootNode.children.push_back(&node->glSecondaryNode());
        }
    }
    else
    {
        for (auto* node : m_scene.orphans())
        {
            m_scene.glScene.nodes.push_back(&node->glSecondaryNode());
        }
    }

    if (args.dumpMaya)
    {
        *args.dumpMaya << undent << "}" << endl;
    }
}

ExportableAsset::~ExportableAsset() = default;

ExportableAsset::Cleanup::Cleanup()
    :currentTime{ MAnimControl::currentTime() }
{
}

ExportableAsset::Cleanup::~Cleanup()
{
    setCurrentTime(currentTime, true);
}

const std::string& ExportableAsset::prettyJsonString() const
{
    if (m_prettyJsonString.empty() && !m_rawJsonString.empty())
    {
        // Pretty format the JSON
        rapidjson::Document jsonDocument;
        const bool hasParseErrors = jsonDocument.Parse(m_rawJsonString.c_str()).HasParseError();

        if (hasParseErrors)
        {
            cerr << prefix << "Failed to reformat glTF JSON, outputting raw JSON" << endl;
            m_prettyJsonString = m_rawJsonString;
        }
        else
        {
            rapidjson::StringBuffer jsonPrettyBuffer;

            // Write the pretty JSON
            rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonPrettyWriter(jsonPrettyBuffer);
            jsonDocument.Accept(jsonPrettyWriter);
            m_prettyJsonString = jsonPrettyBuffer.GetString();
        }
    }

    return m_prettyJsonString;
}

void ExportableAsset::save()
{
    const auto& args = m_resources.arguments();

    const auto sceneName = std::string(args.sceneName.asChar());

    const auto outputFolder = path(args.outputFolder.asChar());

    std::cerr << prefix << "Creating " << outputFolder << "..." << endl;

    for (int retry = 0; retry < 10; ++retry)
    {
        // It seems this can fail with "operation not permitted" if the recursive deletion above is not flushed yet on NTFS
        std::error_code errorCode;
        create_directories(outputFolder, errorCode);
        if (!errorCode)
            break;

        std::cerr << prefix << "Waiting for " << outputFolder << " to be created..." << endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Last try, this will throw an exception if it fails.
    create_directories(outputFolder);

    const auto embed = args.glb || args.embedded;

    const auto allAccessors = m_glAsset.getAllAccessors();

    if (args.dumpAccessorComponents)
    {
        dumpAccessorComponents(allAccessors);
    }


    AccessorPacker bufferPacker;

    PackedBufferMap packedBufferMap;

    // NOTE: when exporting glb, we always merge everything into a single buffer.
    if (!args.glb && !args.separateAccessorBuffers && args.splitMeshAnimation)
    {
        // Combine mesh and clip accessors into two separate buffers

        // Gather mesh accessors, per dag-path
        AccessorsPerDagPath meshAccessorsPerDagPath;
        m_scene.getAllAccessors(meshAccessorsPerDagPath);

        // Compute animation clip accessors
        std::vector<GLTF::Accessor*> animAccessors;

        // Flatten mesh accessors into a set.
        std::set<GLTF::Accessor*> meshAccessorSet;
        for (auto& pair : meshAccessorsPerDagPath)
        {
            std::copy(pair.second.begin(), pair.second.end(), std::inserter(meshAccessorSet, meshAccessorSet.end()));
        }

        // Clip accessors = allAccessors - meshAccessorSet
        for (auto accessor : allAccessors)
        {
            if (meshAccessorSet.find(accessor) == meshAccessorSet.end())
            {
                animAccessors.emplace_back(accessor);
            }
        }

        packMeshAccessors(meshAccessorsPerDagPath, bufferPacker, packedBufferMap, "/mesh");

        // TODO: Also associate clips with dag-paths!
        const auto animBufferName = sceneName+"/anim";
        const auto animBuffer = bufferPacker.packAccessors(animAccessors, animBufferName);
        if (animBuffer)
        {
            packedBufferMap[animBuffer] = animBufferName;
        }
    }
    else if (!args.glb && args.separateAccessorBuffers)
    {
        // Keep every accessor separate, useful for debugging.
        auto index = 0;
        for (auto accessor : allAccessors)
        {
            const auto name = accessor->name.empty() ? "buffer" + std::to_string(index) : accessor->name;
            accessor->bufferView->name = name;
            accessor->bufferView->buffer->name = name;
            packedBufferMap[accessor->bufferView->buffer] = name;
            ++index;
        }
    }
    else
    {
        // Pack everything into a single buffer (default and glb case)
        const auto bufferName = sceneName + "/data";
        const auto buffer = bufferPacker.packAccessors(allAccessors, bufferName);
        if (buffer)
        {
            packedBufferMap[buffer] = bufferName;
        }
    }

    if (args.niceBufferURIs)
    {
        std::map<std::string, int> bufferNameSuffix;

        for (const auto& pair : packedBufferMap)
        {
            auto buffer = pair.first;
            auto uri = pair.second;
            makeValidFilename(uri);

            auto& suffix = bufferNameSuffix[uri];
            suffix += 1;

            uri += std::to_string(suffix);

            uri += ".bin";

            buffer->uri = uri;
        }
    }

    if (args.hashBufferUri)
    {
        // Generate hash buffer URIs 
        for (const auto& pair : packedBufferMap)
        {
            auto buffer = pair.first;

            std::string hash_hex_str;
            picosha2::hash256_hex_string(buffer->data, buffer->data + buffer->byteLength, hash_hex_str);

            std::string filename = pair.second;
            makeValidFilename(filename);
            filename += '_';
            filename += hash_hex_str;
            filename += ".bin";

            buffer->uri = filename;
        }
    }

    // Generate glTF JSON file
    rapidjson::StringBuffer jsonStringBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonStringBuffer);
    jsonWriter.StartObject();

    GLTF::Options options;
    options.embeddedBuffers = embed;
    options.embeddedShaders = embed;
    options.embeddedTextures = embed;
    options.name = args.sceneName.asChar();
    options.binary = args.glb;

    m_glAsset.writeJSON(&jsonWriter, &options);
    jsonWriter.EndObject();

    m_rawJsonString = jsonStringBuffer.GetString();

    const auto outputFilename = args.sceneName + "." + (args.glb ? args.glbFileExtension : args.gltfFileExtension);
    const auto outputPath = outputFolder / outputFilename.asChar();

    cout << prefix << "Writing glTF file to '" << outputPath << "'" << endl;

    if (!options.embeddedTextures) {
        for (GLTF::Image* image : m_glAsset.getAllImages()) {
            path uri = outputFolder / image->uri;
            std::ofstream file;
            create(file, uri.generic_string(), ios::out | ios::binary);
            file.write(reinterpret_cast<char*>(image->data), image->byteLength);
            file.close();
        }
    }

    if (!options.embeddedBuffers)
    {
        for (const auto& pair: packedBufferMap)
        {
            const auto buffer = pair.first;
            if (buffer->data && buffer->byteLength)
            {
                path uri = outputFolder / buffer->uri;
                std::ofstream file;
                create(file, uri.generic_string(), ios::out | ios::binary);
                file.write(reinterpret_cast<char*>(buffer->data), buffer->byteLength);
                file.close();
            }
        }
    }

    if (!options.embeddedShaders) {
        for (GLTF::Shader* shader : m_glAsset.getAllShaders()) {
            path uri = outputFolder / shader->uri;
            std::ofstream file;
            create(file, uri.generic_string(), ios::out | ios::binary);
            file.write(shader->source.c_str(), shader->source.length());
            file.close();
        }
    }

    // Write glTF file.
    {
        const auto& jsonString = m_rawJsonString;

        std::ofstream file;
        create(file, outputPath.string(), ios::out | (args.glb ? ios::binary : 0));

        if (args.glb)
        {
            assert(packedBufferMap.size() <= 1);
            const auto maybeBuffer = packedBufferMap.empty() ? nullptr : packedBufferMap.begin()->first;
            const auto bufferLength = maybeBuffer ? maybeBuffer->byteLength : 0;

            file.write("glTF", 4); // magic header

            const auto writeHeader = new uint32_t[2];
            writeHeader[0] = 2; // version

            const int jsonLength = static_cast<int>(jsonString.length());
            const int jsonPadding = (4 - (jsonLength & 3)) & 3;
            const int binPadding = (4 - (bufferLength & 3)) & 3;

            const int headerLength = 12;
            const int chunkHeaderLength = 8;

            writeHeader[1] = headerLength +
                (chunkHeaderLength + jsonLength + jsonPadding) +
                (chunkHeaderLength + bufferLength + binPadding); // length

            file.write(reinterpret_cast<char*>(writeHeader), sizeof(uint32_t) * 2); // GLB header

            writeHeader[0] = jsonLength + jsonPadding; // chunkLength
            writeHeader[1] = 0x4E4F534A; // chunkType JSON
            file.write(reinterpret_cast<char*>(writeHeader), sizeof(uint32_t) * 2);

            file.write(jsonString.c_str(), jsonLength);
            for (int i = 0; i < jsonPadding; i++) {
                file.write(" ", 1);
            }

            if (bufferLength)
            {
                writeHeader[0] = bufferLength + binPadding; // chunkLength
                writeHeader[1] = 0x004E4942; // chunkType BIN
                file.write(reinterpret_cast<char*>(writeHeader), sizeof(uint32_t) * 2);

                file.write(reinterpret_cast<char*>(maybeBuffer->data), bufferLength);
                for (int i = 0; i < binPadding; i++) {
                    file.write("\0", 1);
                }
            }

        }
        else
        {
            file << prettyJsonString() << endl;
        }

        file.close();
    }

    if (args.dumpGLTF)
    {
        auto& out = *args.dumpGLTF;
        out << "glTF dump:" << endl;
        out << prettyJsonString();
        out << endl;
    }
}

void ExportableAsset::dumpAccessorComponents(const std::vector<GLTF::Accessor*>& accessors) const
{
    // NOTE: Because formatting with std::ostream is so slow, 
    // we use the milo.h implementation for fast floating point printing.
    const auto& args = m_resources.arguments();
    const auto outputFolder = path(args.outputFolder.asChar());

    int fileIndex = 0;

    for (auto&& accessor : accessors)
    {
        // TODO: Add support for integers
        if (accessor->componentType != WebGL::FLOAT)
            continue;

        std::ofstream ofs;
        std::string filename = accessor->name;
        if (filename.empty())
        {
            filename = std::string(args.sceneName.asChar()) + "_" + std::to_string(fileIndex);
        }

        makeValidFilename(filename);

        ofs.open((outputFolder / (filename + ".txt")).c_str(), std::ofstream::out | std::ofstream::binary);

        ++fileIndex;

        const float* data = reinterpret_cast<float*>(accessor->bufferView->buffer->data);

        const int dimension = GLTF::Accessor::getNumberOfComponents(accessor->type);

        const int rowBufferSize = dimension * fmt::BUFFER_SIZE + 2 * (dimension + 1);
        const auto rowBuffer = static_cast<char*>(alloca(rowBufferSize));

        const auto colWidth = 16;

        for (int row = 0; row < accessor->count; ++row)
        {
            char* str = rowBuffer;
            char* end = str;

            int step = 0;

            for (int col = 0; col < dimension; ++col)
            {
                while (str < end) *str++ = ' ';
                end = str + colWidth;
                str = fmt::format_double(str, data[col], 8);
            }

            *str++ = '\n';

            assert((str - rowBuffer) <= rowBufferSize);

            ofs.write(rowBuffer, str - rowBuffer);

            data += dimension;
        }

        ofs.close();
    }
}


void ExportableAsset::packMeshAccessors(
    AccessorsPerDagPath& accessorsPerDagPath,
    AccessorPacker& packer,
    PackedBufferMap& packedBufferMap,
    std::string nameSuffix) const
{
    AccessorsPerDagPath remainingAccessorsPerDagPath = accessorsPerDagPath;

    const auto& args = m_resources.arguments();

    if (args.splitByReference)
    {
        MFileIO fileIO;

        MStringArray refNames;
        THROW_ON_FAILURE(fileIO.getReferences(refNames));

        for (auto refIndex = 0U; refIndex < refNames.length(); ++refIndex)
        {
            auto refFile = refNames[refIndex];

            // NOTE: Using the much easier MFileIO::getReferenceNodes MSelectionSet overload hangs Maya
            MStringArray refNodes;
            THROW_ON_FAILURE(MFileIO::getReferenceNodes(refFile, refNodes));

            std::set<std::string> refNodeSet;
            for (auto i = 0U; i < refNodes.length(); ++i)
            {
                std::string refNodeName = refNodes[i].asChar();
                refNodeSet.insert(refNodeName);
            }

            std::vector<GLTF::Accessor*> refAccessors;
            for (auto& pair : accessorsPerDagPath)
            {
                std::string fullName = pair.first.partialPathName().asChar();
                if (refNodeSet.find(fullName) != refNodeSet.end())
                {
                    remainingAccessorsPerDagPath.erase(pair.first);
                    std::copy(pair.second.begin(), pair.second.end(), std::back_inserter(refAccessors));
                }
            }

            path refPath(refFile.asChar());
            auto refStem = refPath.stem().generic_string();

            const auto bufferName = refStem + nameSuffix;
            const auto buffer = packer.packAccessors(refAccessors, bufferName);

            packedBufferMap[buffer] = bufferName;
        }

        if (!remainingAccessorsPerDagPath.empty())
        {
            std::cerr << prefix << "WARNING: Found unreferenced meshes in scene but -splitByReference flag was passed! Merging all these meshes into a single buffer" << endl;
        }
    }

    // Pack all remaining accessors into a single buffer.
    {
        std::vector<GLTF::Accessor*> flatAccessors;

        for (auto& pair : remainingAccessorsPerDagPath)
        {
            std::copy(pair.second.begin(), pair.second.end(), std::back_inserter(flatAccessors));
        }

        const auto bufferName = args.sceneName.asChar() + nameSuffix;
        const auto buffer = packer.packAccessors(flatAccessors, bufferName);

        if (buffer)
        {
            packedBufferMap[buffer] = bufferName;
        }
    }
}

void ExportableAsset::create(std::ofstream& file, const std::string& path, const std::ios_base::openmode mode)
{
    file.open(path, mode);

    if (!file.is_open())
    {
        std::ostringstream ss;
        ss << "Couldn't write to '" << path << "'";
        throw std::runtime_error(ss.str().c_str());
    }
}
