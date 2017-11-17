#include "externals.h"
#include "MeshBlendShapes.h"
#include "MayaException.h"
#include "dump.h"
#include "DagHelper.h"
#include "MayaUtils.h"
#include "MeshBlendShapeWeights.h"

MeshBlendShapes::MeshBlendShapes(MObject blendShapeController)
{
	MStatus status;

	MFnDependencyNode fnController(blendShapeController, &status);
	THROW_ON_FAILURE(status);

	cout << "Processing blend shapes of " << fnController.name().asChar() << "..." << endl;

	MPlug inputsPlug = fnController.findPlug("input", &status);
	THROW_ON_FAILURE(status);

	const auto numElements = inputsPlug.evaluateNumElements(&status);
	THROW_ON_FAILURE(status);
	if (numElements == 0)
	{
		MayaException::printError("Blend shape controller has no inputs!");
		return;
	}

	const MPlug inputPlug = inputsPlug.elementByPhysicalIndex(0, &status);
	THROW_ON_FAILURE(status);

	const MPlug inputGeometryPlug = DagHelper::getChildPlug(inputPlug, "inputGeometry");
	if (inputGeometryPlug.isNull())
	{
		MayaException::printError("Blend shape controller has no input geometry plug!");
		return;
	}

	MObject baseObject = getOrCreateIncomingShapeNode(inputGeometryPlug);
	if (baseObject == MObject::kNullObj)
	{
		MayaException::printError("Blend shape controller has no input geometry!");
		return;
	}

	MFnMesh mesh(baseObject, &status);
	cout << "Blend neutral shape = " << mesh.name() << endl;
	THROW_ON_FAILURE(status);

	MPlug inputTargetArrayPlug = fnController.findPlug("inputTarget", &status);
	THROW_ON_FAILURE(status);

	MPlug weightArrayPlug = fnController.findPlug("weight", &status);
	THROW_ON_FAILURE(status);

	auto nextIndex = 0;

	const auto inputTargetCount = inputTargetArrayPlug.evaluateNumElements(&status);
	THROW_ON_FAILURE(status);

	MPlug outputGeometryPlugs = fnController.findPlug("outputGeometry", &status);
	THROW_ON_FAILURE(status);

	const auto outputGeometryPlugsDimension = outputGeometryPlugs.evaluateNumElements(&status);
	THROW_ON_FAILURE(status);

	if (outputGeometryPlugsDimension == 0)
	{
		MayaException::printError("Blend shape controller output geometry is not connected to anything!");
		return;
	}

	m_baseShape = std::make_unique<MeshShape>(mesh);

	for (uint targetIndex = 0; targetIndex < inputTargetCount; ++targetIndex)
	{
		const auto inputTargetPlug = inputTargetArrayPlug.elementByPhysicalIndex(targetIndex, &status);
		THROW_ON_FAILURE(status);

		auto inputTargetGroupArrayPlug = DagHelper::getChildPlug(inputTargetPlug, "inputTargetGroup");

		const auto inputTargetGroupCount = inputTargetGroupArrayPlug.evaluateNumElements(&status);
		THROW_ON_FAILURE(status);

		for (uint groupIndex = 0; groupIndex < inputTargetGroupCount; ++groupIndex)
		{
			const auto inputTargetGroupPlug = inputTargetGroupArrayPlug.elementByPhysicalIndex(groupIndex, &status);
			THROW_ON_FAILURE(status);

			auto inputTargetInputArrayPlug = DagHelper::getChildPlug(inputTargetGroupPlug, "inputTargetInput");
			if (inputTargetInputArrayPlug.isNull())
			{
				MayaException::printError(formatted("Blend shape controller's target#%d, group#%d, has no inputTargetInput plug!", targetIndex, groupIndex));
				continue;
			}

			const auto inputTargetInputCount = inputTargetInputArrayPlug.evaluateNumElements(&status);
			THROW_ON_FAILURE(status);

			for (uint inputIndex = 0; inputIndex < inputTargetInputCount; ++inputIndex)
			{
				const auto inputTargetInput = inputTargetInputArrayPlug.elementByPhysicalIndex(inputIndex, &status);
				THROW_ON_FAILURE(status);

				MPlug inputGeometryTargetPlug = DagHelper::getChildPlug(inputTargetInput, "inputGeomTarget");
				if (inputGeometryTargetPlug.isNull())
				{
					MayaException::printError(formatted("Blend shape controller's target#%d, group#%d, input#%d has no inputGeomTarget plug!", targetIndex, groupIndex, inputIndex));
					continue;
				}

				MPlug weightPlug = weightArrayPlug.elementByLogicalIndex(inputIndex, &status);
				THROW_ON_FAILURE(status);

				const auto isInstanced = DagHelper::hasConnection(inputGeometryTargetPlug, false, true);
				if (isInstanced)
				{
					// The original blend shape target mesh is still part of the history,
					// so we can extract full information (normals, tangents, etc) from the mesh.
					MObject targetObj = getOrCreateIncomingShapeNode(inputGeometryTargetPlug);

					if (targetObj.isNull())
					{
						MayaException::printError(formatted("getOrCreateIncomingShapeNode failed for target #%d!", inputIndex));
					}
					else
					{
						MFnMesh blendShapeTargetMesh(targetObj, &status);
						THROW_ON_FAILURE(status);

						cout << "Found blend shape target " << blendShapeTargetMesh.name() << endl;

						m_blendShapes.emplace_back(std::make_unique<MeshBlendShape>(blendShapeTargetMesh, weightPlug));
					}
				}
				else
				{
					// The mesh is not in Maya anymore...
					// We only have access to the blendshape positions deltas, not the normals...
					// We create a temporary shape node at the blend shape controller's geometry output,
					// and mutually exclusively set each weight to one, reconstructing the original blend shapes.
					cout << "The original blend shape target mesh was deleted; reconstructing blend shape normals..." << endl;

					// We use the MeshBlendShapeWeights helper class to manipulate the weights 
					// in order to reconstruct the geometry of deleted blend shape targets.
					// When an exception is thrown, the weights and connections will be restored.
					MeshBlendShapeWeights weightPlugs(weightArrayPlug);
					weightPlugs.breakConnections();

					MPlug outputGeometryPlug = outputGeometryPlugs.elementByPhysicalIndex(0, &status);
					THROW_ON_FAILURE(status);

					MObject outputMeshObj = getOrCreateOutgoingShapeNode(outputGeometryPlug);

					if (outputMeshObj.isNull())
					{
						MayaException::printError(formatted("getOrCreateOutgoingShapeNode failed for target #%d!", inputIndex));
					}
					else
					{
						weightPlugs.setFullWeightAndClearOthers(inputIndex);

						MFnMesh blendShapeTargetMesh(outputMeshObj, &status);
						THROW_ON_FAILURE(status);

						cout << "Reconstructed blend shape target " << blendShapeTargetMesh.name() << endl;

						m_blendShapes.emplace_back(std::make_unique<MeshBlendShape>(blendShapeTargetMesh, weightPlug));
					}
				}
			}
		}
	}
}


MeshBlendShapes::~MeshBlendShapes()
{
	// TODO: Delete temporary created shapes
}

void MeshBlendShapes::dump(const std::string& name, const std::string& indent) const
{
	cout << indent << quoted(name) << ": {" << endl;
	const auto subIndent = indent + "\t";

	if (m_baseShape)
	{
		m_baseShape->dump("base", subIndent);
	}
	else
	{
		cout << subIndent << "base: null";
	}

	cout << "," << endl;

	for (auto i=0; i<m_blendShapes.size(); ++i)
	{
		m_blendShapes.at(i)->shape.dump(std::string("target#") + std::to_string(i), subIndent);
		cout << "," << endl;
	}

	cout << indent << "}";
}

MObject MeshBlendShapes::getOrCreateIncomingShapeNode(const MPlug& inputGeometryPlug) const
{
	MStatus status;
	MPlugArray connections;
	inputGeometryPlug.connectedTo(connections, true, false, &status);
	THROW_ON_FAILURE(status);

	if (connections.length() == 0)
		return MObject::kNullObj;

	MPlug sourcePlug = connections[0];
	MObject sourceNode = sourcePlug.node();

	if (sourceNode.isNull())
		return MObject::kNullObj;

	if (sourceNode.hasFn(MFn::kMesh))
		return sourceNode;

	// The blend-shape geometry is not connected to a mesh, create one.

	// Create the mesh node
	MDagModifier dagMod;
	const MObject tempNode = dagMod.createNode("mesh", MObject::kNullObj, &status);
	THROW_ON_FAILURE(dagMod.doIt());

	// Make sure we select the shape node, not the transform node.
	MDagPath meshDagPath = MDagPath::getAPathTo(tempNode, &status);
	THROW_ON_FAILURE(status);
	THROW_ON_FAILURE(meshDagPath.extendToShape());

	// Connect the mesh node
	// NOTE: The node does not yet have an MFnMesh interface!!!
	// This only happens when it is connected to another node that delivers geometry...
	MFnDagNode dagFn(meshDagPath, &status);
	THROW_ON_FAILURE(status);

	const auto newSuggestedName = utils::simpleName(inputGeometryPlug.name(&status));
	THROW_ON_FAILURE(status);

	const auto newName = dagFn.setName(newSuggestedName, &status);
	THROW_ON_FAILURE(status);

	cout << "Created temporary incoming shape " << newName << endl;

	// Make the mesh invisible
	MPlug intermediateObjectPlug = dagFn.findPlug("intermediateObject", &status);
	THROW_ON_FAILURE(status);
	THROW_ON_FAILURE(intermediateObjectPlug.setBool(true));

	MPlug inMeshPlug = dagFn.findPlug("inMesh", &status);
	THROW_ON_FAILURE(status);

	MPlug outMeshPlug = dagFn.findPlug("outMesh", &status);
	THROW_ON_FAILURE(status);

	MDGModifier dgMod;
	THROW_ON_FAILURE(dgMod.disconnect(sourcePlug, inputGeometryPlug));
	THROW_ON_FAILURE(dgMod.doIt());

	THROW_ON_FAILURE(dgMod.connect(outMeshPlug, inputGeometryPlug));
	THROW_ON_FAILURE(dgMod.doIt());

	THROW_ON_FAILURE(dgMod.connect(sourcePlug, inMeshPlug));
	THROW_ON_FAILURE(dgMod.doIt());

	// Should now be a mesh...
	if (!meshDagPath.hasFn(MFn::kMesh))
		return MObject::kNullObj;

	MObject mesh = meshDagPath.node(&status);
	THROW_ON_FAILURE(status);
	return mesh;
}


MObject MeshBlendShapes::getOrCreateOutgoingShapeNode(MPlug& outputGeometryPlug) const
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
		MObject tempNode = dagMod.createNode("mesh", MObject::kNullObj, &status);
		THROW_ON_FAILURE(dagMod.doIt());

		// Make sure we select the shape node, not the transform node.
		MDagPath meshDagPath = MDagPath::getAPathTo(tempNode, &status);
		THROW_ON_FAILURE(status);
		THROW_ON_FAILURE(meshDagPath.extendToShape());

		// NOTE: The node does not yet have an MFnMesh interface!!!
		// This only happens when it is connected to another node that delivers geometry...
		MFnDagNode dagFn(meshDagPath, &status);
		THROW_ON_FAILURE(status);

		MString newSuggestedName = utils::simpleName(outputGeometryPlug.name(&status));
		THROW_ON_FAILURE(status);

		MString newName = dagFn.setName(newSuggestedName, &status);
		THROW_ON_FAILURE(status);

		cout << "Created temporary outgoing shape " << newName << endl;

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
