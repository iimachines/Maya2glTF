#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "Mesh.h"
#include "Arguments.h"

ExportableNode::ExportableNode(MDagPath dagPath, MString name, ExportableResources& resources, const Arguments& args)
{
	MStatus status;

	glNode.transform = &m_matrix;

	// We assume the shape is selected here, so we need to take the transform of the parent
	MFnDagNode fnShapeNode(dagPath);
	MObject parentNode = fnShapeNode.parent(0, &status);
	THROW_ON_FAILURE(status);

	MFnDagNode fnParentnode(parentNode, &status);
	THROW_ON_FAILURE(status);

	auto transform = fnParentnode.transformationMatrix(&status);
	THROW_ON_FAILURE(status);

	float m[4][4];
	transform.get(m);

	m_matrix = GLTF::Node::TransformMatrix(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]);

	// TODO: Initialize transform.
	switch (dagPath.apiType(&status))
	{
	case MFn::kMesh:
	{
		Mesh mayaMesh(dagPath);

		if (args.dumpMaya)
		{
			mayaMesh.dump(dagPath.fullPathName().asChar(), "");
		}

		m_mesh = std::make_unique<ExportableMesh>(mayaMesh, resources);
		glNode.mesh = &m_mesh->glMesh;
	}
	break;
	default:
		cerr << "glTF2Maya: skipping '" << name.asChar() << "', it is not supported" << endl;
		break;
	}
}

ExportableNode::~ExportableNode()
{
}

std::unique_ptr<ExportableNode> ExportableNode::from(MDagPath dagPath, ExportableResources& usedShaderNames, const Arguments& args)
{
	MStatus status;

	MString name = dagPath.partialPathName(&status);
	THROW_ON_FAILURE(status);

	dagPath.extendToShape();

	MObject mayaNode = dagPath.node(&status);
	if (mayaNode.isNull() || status.error())
	{
		cerr << "glTF2Maya: skipping '" << name.asChar() << "' as it is not a node" << endl;
		return nullptr;
	}

	return std::make_unique<ExportableNode>(dagPath, name, usedShaderNames, args);
}
