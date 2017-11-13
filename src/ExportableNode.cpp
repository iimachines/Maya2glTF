#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"


ExportableNode::ExportableNode(MDagPath dagPath, MString name)
{
	MStatus status;

	// TODO: Initialize transform.
	switch (dagPath.apiType(&status))
	{
	case MFn::kMesh:
		m_mesh = std::make_unique<ExportableMesh>(dagPath);
		glNode.mesh = &m_mesh->glMesh;
		break;
	default:
		cerr << "glTF2Maya: skipping '" << name.asChar() << "', it is not supported" << endl;
		break;
	}
}

ExportableNode::~ExportableNode()
{
}

std::unique_ptr<ExportableNode> ExportableNode::from(MDagPath dagPath)
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

	return std::make_unique<ExportableNode>(dagPath, name);
}
