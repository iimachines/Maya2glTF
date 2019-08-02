#include "externals.h"
#include "Mesh.h"
#include "MayaException.h"
#include "Arguments.h"
#include "MayaUtils.h"
#include "MeshBlendShapeWeights.h"
#include "DagHelper.h"
#include "ExportableScene.h"

Mesh::Mesh(ExportableScene& scene, MDagPath dagPath, const ExportableNode& node)
{
    MStatus status = dagPath.extendToShape();
    THROW_ON_FAILURE(status);

    auto& args = scene.arguments();

    MFnMesh fnMesh(dagPath, &status);
    THROW_ON_FAILURE(status);

    MObject blendShapeDeformer = args.skipBlendShapes
        ? MObject::kNullObj
        : tryExtractBlendShapeDeformer(fnMesh, args.ignoreMeshDeformers);

    if (blendShapeDeformer.isNull())
    {
        // Single shape
        m_mainShape = std::make_unique<MainShape>(scene, fnMesh, node, ShapeIndex::main());
        m_allShapes.emplace_back(m_mainShape.get());
    }
    else
    {
        // Shape with morph targets.
        MFnBlendShapeDeformer fnBlendShapeDeformer(blendShapeDeformer, &status);
        THROW_ON_FAILURE(status);

        const auto deformerName = fnBlendShapeDeformer.name().asChar();
        cout << prefix << "Processing blend shapes of " << deformerName << "..." << endl;

        const MPlug weightArrayPlug = fnBlendShapeDeformer.findPlug("weight", &status);
        THROW_ON_FAILURE(status);

        // We use the MeshBlendShapeWeights helper class to manipulate the weights 
        // in order to reconstruct the geometry of deleted blend shape targets.
        // When an exception is thrown, the weights and connections will be restored.
        MeshBlendShapeWeights weightPlugs(weightArrayPlug);
        weightPlugs.breakConnections();

        auto& weightEntries = weightPlugs.entries();

        for (auto && pair : weightEntries)
        {
            cout << prefix << "target#" << pair.second.shapeIndex << ": " << std::quoted(pair.first, '\'') << endl;
            cout.flush();
        }

        // Clear all weights to reconstruct base mesh
        weightPlugs.clearWeightsExceptFor(nullptr);

        // Reconstruct base mesh
        m_mainShape = std::make_unique<MainShape>(scene, fnMesh, node, ShapeIndex::main());
        m_allShapes.emplace_back(m_mainShape.get());

        for (auto && pair : weightEntries)
        {
            auto& entry = pair.second;
            weightPlugs.clearWeightsExceptFor(&entry);
            auto weightPlug = weightPlugs.getWeightPlug(entry);
            auto initialWeight = static_cast<float>(entry.originalWeight);
            auto blendShape = std::make_unique<MeshShape>(m_mainShape->indices(),
                fnMesh, node,
                args,
                ShapeIndex::target(entry.shapeIndex),
                weightPlug, initialWeight);
            m_allShapes.emplace_back(blendShape.get());
            m_blendShapes.emplace_back(std::move(blendShape));
        }
    }
}

Mesh::~Mesh() = default;

MObject Mesh::tryExtractBlendShapeDeformer(const MFnMesh& fnMesh, const MSelectionList& ignoredDeformers)
{
    MObject deformer;
    int animatedPlugCount = 0;

    // Iterate upstream to find all the nodes that affect the mesh.
    MStatus status;
    MPlug plug = fnMesh.findPlug("inMesh", status);
    THROW_ON_FAILURE(status);

    // TODO: Also look into inverted blend shapes through skinning, pose space deformations, etc..
    if (plug.isConnected())
    {
        MItDependencyGraph dgIt(plug,
            MFn::kInvalid,
            MItDependencyGraph::kUpstream,
            MItDependencyGraph::kBreadthFirst,
            MItDependencyGraph::kNodeLevel,
            &status);

        THROW_ON_FAILURE(status);

        dgIt.disablePruningOnFilter();

        for (; !dgIt.isDone(); dgIt.next())
        {
            MObject thisNode = dgIt.thisNode();
            if (thisNode.hasFn(MFn::kBlendShape))
            {
                MFnBlendShapeDeformer fnDeformer(thisNode, &status);

                MFnDependencyNode dpNode(thisNode);

                const auto thisName = dpNode.name();

                if (status == MStatus::kSuccess)
                {
                    bool isIgnored = false;
                    DagHelper::getPlugValue(thisNode, "MGi", isIgnored);
                    if (isIgnored || ignoredDeformers.hasItem(thisNode))
                    {
                        cout << prefix << "ignoring blend shape deformer " << thisName << endl;
                    }
                    else if (deformer.isNull())
                    {
                        cout << prefix << "using blend shape deformer " << thisName << endl;
                        deformer = thisNode;
                    }
                    else
                    {
                        // If we find more than one blend shape deformer, pick the one with most animated weights.
                        const MPlug weightArrayPlug = fnDeformer.findPlug("weight", &status);
                        THROW_ON_FAILURE(status);

                        MeshBlendShapeWeights weightPlugs(weightArrayPlug);

                        const auto newAnimatedPlugCount = weightPlugs.animatedPlugCount();

                        auto skippedName = thisName;
                        auto skippedAnimatedPlugCount = newAnimatedPlugCount;

                        if (newAnimatedPlugCount > animatedPlugCount)
                        {
                            skippedAnimatedPlugCount = animatedPlugCount;

                            MFnDependencyNode skippedNode(deformer);
                            skippedName = skippedNode.name();

                            deformer = thisNode;
                            animatedPlugCount = newAnimatedPlugCount;
                        }

                        cerr << prefix << "WARNING: only a single blend shape deformer is supported, skipping " << skippedName << ", it has less animated weight plugs " << skippedAnimatedPlugCount << " vs " << animatedPlugCount <<  endl;
                    }
                }
                else
                {
                    cerr << prefix << "WARNING: unable to extract blend deformer from " << thisName << ", reason: " << status.error() << endl;
                }
            }
        }
    }

    return deformer;
}

void Mesh::dump(class IndentableStream& out, const std::string& name) const
{
    out << quoted(name) << ": {" << endl << indent;

    JsonSeparator sep(",\n");

    for (auto& shape : m_allShapes)
    {
        out << sep;
        shape->dump(out, std::string("shape#") + std::to_string(shape->shapeIndex.arrayIndex()));
    }

    out << undent << '}';
}

Mesh::Cleanup::~Cleanup()
{
    if (!tempOutputMesh.isNull())
    {
        MDagModifier dagMod;
        dagMod.deleteNode(tempOutputMesh);
        tempOutputMesh = MObject::kNullObj;
    }
}

MObject Mesh::getOrCreateOutputShape(MPlug& outputGeometryPlug, MObject& createdMesh) const
{
    MStatus status;
    MPlugArray connections;
    outputGeometryPlug.connectedTo(connections, false, true, &status);
    THROW_ON_FAILURE(status);

    MObject meshNode = MObject::kNullObj;

    for (auto i = 0U; i < connections.length() && meshNode.isNull(); ++i)
    {
        MPlug targetPlug = connections[i];
        MObject targetNode = targetPlug.node();

        if (!targetNode.isNull())
        {
            if (targetNode.hasFn(MFn::kMesh))
            {
                meshNode = targetNode;
            }
        }
    }

    if (meshNode.isNull())
    {
        // Not connected to a mesh, create one.

        // Create the mesh node
        MDagModifier dagMod;
        createdMesh = dagMod.createNode("mesh", MObject::kNullObj, &status);
        THROW_ON_FAILURE(dagMod.doIt());

        // Make sure we select the shape node, not the transform node.
        MDagPath meshDagPath = MDagPath::getAPathTo(createdMesh, &status);
        THROW_ON_FAILURE(status);
        THROW_ON_FAILURE(meshDagPath.extendToShape());

        // NOTE: The node does not yet have an MFnMesh interface!!!
        // This only happens when it is connected to another node that delivers geometry...
        MFnDagNode dagFn(meshDagPath, &status);
        THROW_ON_FAILURE(status);

        const MString newSuggestedName = "maya2glTW_" + utils::simpleName(outputGeometryPlug.name(&status));
        THROW_ON_FAILURE(status);

        const MString newName = dagFn.setName(newSuggestedName, &status);
        THROW_ON_FAILURE(status);

        cout << prefix << "Created temporary output mesh '" << newName << "'. This will be deleted after exporting, but Maya will think your scene is modified, and warn you." << endl;

        // Make the mesh invisible
        MPlug intermediateObjectPlug = dagFn.findPlug("intermediateObject", &status);
        THROW_ON_FAILURE(status);
        THROW_ON_FAILURE(intermediateObjectPlug.setBool(true));

        MDGModifier dgMod;

        MPlug inMeshPlug = dagFn.findPlug("inMesh", &status);
        THROW_ON_FAILURE(status);

        THROW_ON_FAILURE(dgMod.connect(outputGeometryPlug, inMeshPlug));
        THROW_ON_FAILURE(dgMod.doIt());

        // Should now be a mesh...
        if (meshDagPath.hasFn(MFn::kMesh))
        {
            meshNode = meshDagPath.node(&status);
            THROW_ON_FAILURE(status);
        }
    }

    return meshNode;
}

