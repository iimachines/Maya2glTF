#include "externals.h"
#include "Exporter.h"
#include "MayaException.h"
#include "Arguments.h"
#include "SignalHandlers.h"
#include "ExportableMesh.h"
#include "ExportableNode.h"

void create(std::ofstream& file, const std::string& path, const std::ios_base::openmode mode)
{
	file.open(path, mode);

	if (!file.is_open())
	{
		std::ostringstream ss;
		ss << "Couldn't write to '" << path << "'";
		throw std::exception(ss.str().c_str());
	}
}

Exporter::Exporter()
{
}

Exporter::~Exporter()
{
}

void* Exporter::createInstance()
{
	return new Exporter();
}

MStatus Exporter::doIt(const MArgList& args)
{
	SignalHandlers signalHandlers;

	try
	{
		std::cout << "maya2glTF: Parsing arguments..." << endl;
		const Arguments arguments(args, syntax());

		std::cout << "maya2glTF: Starting export..." << endl;
		exportScene(arguments);

		return MStatus::kSuccess;
	}
	catch (const MayaException &ex)
	{
		return MayaException::printError(ex.what(), ex.status);
	}
	catch (const std::exception &ex)
	{
		return MayaException::printError(ex.what());
	}
	catch (...)
	{
		return MayaException::printError("maya2glTF: Unexpected fatal error!");
	}
}

bool Exporter::isUndoable() const
{
	return false;
}

bool Exporter::hasSyntax() const
{
	return true;
}

void Exporter::exportScene(const Arguments& args)
{
	MStatus status;

	auto& selection = args.selection;

	GLTF::Asset glAsset;
	GLTF::Scene glScene;

	glAsset.scenes.push_back(&glScene);
	glAsset.scene = 0;

	std::vector<std::unique_ptr<ExportableItem>> exportables;

	for (uint selectionIndex = 0; selectionIndex < selection.length(); ++selectionIndex)
	{
		MDagPath dagPath;
		THROW_ON_FAILURE(selection.getDagPath(selectionIndex, dagPath));

		auto exportableNode = ExportableNode::from(dagPath);

		if (exportableNode)
		{
			glScene.nodes.push_back(&exportableNode->glNode);
			exportables.push_back(std::move(exportableNode));
		}
	}

	const auto buffer = glAsset.packAccessors();

	// Generate glTF JSON file
	rapidjson::StringBuffer jsonStringBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonStringBuffer);
	jsonWriter.StartObject();

	const auto embed = !args.glb && !args.separate;

	GLTF::Options options;
	options.embeddedBuffers = embed;
	options.embeddedShaders = embed;
	options.embeddedTextures = embed;
	options.name = args.sceneName.asChar();
	options.binary = args.glb;

	glAsset.writeJSON(&jsonWriter, &options);
	jsonWriter.EndObject();

	std::string jsonString = jsonStringBuffer.GetString();

	const auto outputFolder = path(args.outputFolder.asChar());
	create_directories(outputFolder);

	const auto outputFilename = std::string(args.sceneName.asChar()) + (args.glb ? ".glb" : ".glTF");
	const auto outputPath = outputFolder / outputFilename;

	if (!options.embeddedTextures) {
		for (GLTF::Image* image : glAsset.getAllImages()) {
			path uri = outputFolder / image->uri;
			std::ofstream file;
			create(file, uri.generic_string(), ios::out | ios::binary);
			file.write(reinterpret_cast<char*>(image->data), image->byteLength);
			file.close();
		}
	}

	if (!options.embeddedBuffers) {
		path uri = outputFolder / buffer->uri;
		std::ofstream file;
		create(file, uri.generic_string(), ios::out | ios::binary);
		file.write(reinterpret_cast<char*>(buffer->data), buffer->byteLength);
		file.close();
	}

	if (!options.embeddedShaders) {
		for (GLTF::Shader* shader : glAsset.getAllShaders()) {
			path uri = outputFolder / shader->uri;
			std::ofstream file;
			create(file, uri.generic_string(), ios::out | ios::binary);
			file.write(shader->source.c_str(), shader->source.length());
			file.close();
		}
	}

	// Write glTF file.
	{
		std::ofstream file;
		create(file, outputPath.string(), ios::out | (args.glb ? ios::binary : 0));

		if (args.glb)
		{
			file.write("glTF", 4); // magic header

			const auto writeHeader = new uint32_t[2];
			writeHeader[0] = 2; // version

			const int jsonLength = static_cast<int>(jsonString.length());
			const int jsonPadding = (4 - (jsonLength & 3)) & 3;
			const int binPadding = (4 - (buffer->byteLength & 3)) & 3;

			const int headerLength = 12;
			const int chunkHeaderLength = 8;

			writeHeader[1] = headerLength +
				(chunkHeaderLength + jsonLength + jsonPadding) +
				(chunkHeaderLength + buffer->byteLength + binPadding); // length

			file.write(reinterpret_cast<char*>(writeHeader), sizeof(uint32_t) * 2); // GLB header

			writeHeader[0] = jsonLength + jsonPadding; // chunkLength
			writeHeader[1] = 0x4E4F534A; // chunkType JSON
			file.write(reinterpret_cast<char*>(writeHeader), sizeof(uint32_t) * 2);

			file.write(jsonString.c_str(), jsonLength);
			for (int i = 0; i < jsonPadding; i++) {
				file.write(" ", 1);
			}

			writeHeader[0] = buffer->byteLength + binPadding; // chunkLength
			writeHeader[1] = 0x004E4942; // chunkType BIN
			file.write(reinterpret_cast<char*>(writeHeader), sizeof(uint32_t) * 2);

			file.write(reinterpret_cast<char*>(buffer->data), buffer->byteLength);
			for (int i = 0; i < binPadding; i++) {
				file.write("\0", 1);
			}
		}
		else
		{
			// Pretty format the JSON
			rapidjson::Document jsonDocument;
			jsonDocument.Parse(jsonString.c_str());

			rapidjson::StringBuffer jsonPrettyBuffer;
			rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonPrettyWriter(jsonPrettyBuffer);
			jsonDocument.Accept(jsonPrettyWriter);

			const auto prettyString = jsonPrettyBuffer.GetString();

			file << prettyString << endl;

			if (args.print)
			{
				cout << prettyString << endl;
			}
		}

		file.close();
	}
}
