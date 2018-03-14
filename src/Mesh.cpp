#include "externals.h"
#include "Mesh.h"
#include "MayaException.h"
#include "Arguments.h"
#include "MayaUtils.h"
#include "MeshBlendShapeWeights.h"
#include "DagHelper.h"

Mesh::Mesh(const MDagPath& dagPath, const Arguments& args)
{
	MStatus status;

	MFnMesh fnMesh(dagPath, &status);
	THROW_ON_FAILURE(status);

	MObject blendShapeDeformer = tryExtractBlendShapeDeformer(fnMesh, args.ignoreMeshDeformers);

	if (blendShapeDeformer.isNull())
	{
		// Single shape
		m_shapes.emplace_back(std::make_unique<MeshShape>(fnMesh, args, ShapeIndex::main(), MPlug(), 0.0f));
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

		std::unique_ptr<MFnMesh> fnDeformedMesh;

		if (args.blendFinalMesh)
		{
			fnDeformedMesh = std::make_unique<MFnMesh>(dagPath, &status);
		}
		else
		{
			MPlug outputGeometryPlugs = fnBlendShapeDeformer.findPlug("outputGeometry", &status);
			THROW_ON_FAILURE(status);

			const auto outputGeometryPlugsDimension = outputGeometryPlugs.evaluateNumElements(&status);
			THROW_ON_FAILURE(status);

			if (outputGeometryPlugsDimension == 0)
				THROW_ON_FAILURE_WITH(MStatus::kFailure, formatted("Output geometry of %s is not connected to anything!", deformerName));

			MPlug outputGeometryPlug = outputGeometryPlugs.elementByPhysicalIndex(0, &status);
			THROW_ON_FAILURE(status);

			MObject outputShape = getOrCreateOutputShape(outputGeometryPlug, m_cleanup.tempOutputMesh);

			if (outputShape.isNull())
				THROW_ON_FAILURE_WITH(MStatus::kFailure, formatted("Could not get output geometry of %s!", deformerName));

			fnDeformedMesh = std::make_unique<MFnMesh>(outputShape, &status);
			THROW_ON_FAILURE(status);
		}

		// We use the MeshBlendShapeWeights helper class to manipulate the weights 
		// in order to reconstruct the geometry of deleted blend shape targets.
		// When an exception is thrown, the weights and connections will be restored.
		MeshBlendShapeWeights weightPlugs(weightArrayPlug);
		weightPlugs.breakConnections();

		// Clear all weights to reconstruct base mesh
		weightPlugs.clearWeightsExceptFor(-1);

		// Reconstruct base mesh
		m_shapes.emplace_back(std::make_unique<MeshShape>(*fnDeformedMesh, args, ShapeIndex::main(), MPlug(), 0.0f));

		const auto numWeights = weightPlugs.numWeights();

		for (auto targetIndex = 0U; targetIndex < numWeights; targetIndex++)
		{
			weightPlugs.clearWeightsExceptFor(targetIndex);
			auto weightPlug = weightPlugs.getWeightPlug(targetIndex);
			auto initialWeight = static_cast<float>(weightPlugs.getOriginalWeight(targetIndex));
			m_shapes.emplace_back(std::make_unique<MeshShape>(*fnDeformedMesh, args, ShapeIndex::target(targetIndex), weightPlug, initialWeight));
		}
	}
}

Mesh::~Mesh() = default;

MObject Mesh::tryExtractBlendShapeDeformer(const MFnMesh& fnMesh, const MSelectionList& ignoredDeformers)
{
	MObject deformer;

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

				const auto thisName = MFnDependencyNode(thisNode).name();

				if (status == MStatus::kSuccess)
				{
					if (ignoredDeformers.hasItem(thisNode))
					{
						cout << prefix << "ignoring blend shape deformer " << thisName << endl;
					}
					else if (deformer.isNull())
					{
						deformer = thisNode;
					}
					else
					{
						cerr << prefix << "only a single blend shape deformer is supported, skipping " << thisName << endl;
					}
				}
				else
				{
					cerr << prefix << "unable to extract blend deformer from " << thisName << ", reason: " << status.error() << endl;
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

	for (auto& shape: m_shapes)
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
