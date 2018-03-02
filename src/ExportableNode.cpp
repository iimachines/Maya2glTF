#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "ExportableClip.h"
#include "Transform.h"

ExportableNode::ExportableNode(MDagPath dagPath, ExportableResources& resources)
	: ExportableObject(dagPath.node())
	, dagPath(dagPath)
{
	MStatus status;

	handleNameAssignment(resources, glNode);

	const auto objectMatrix = Transform::getObjectSpaceMatrix(dagPath);
	m_matrix = Transform::toGLTF(objectMatrix);

	glNode.transform = &m_matrix;

	dagPath.extendToShape();

	switch (dagPath.apiType(&status))
	{
	case MFn::kMesh:
	{
		m_mesh = std::make_unique<ExportableMesh>(dagPath, resources);
		glNode.mesh = &m_mesh->glMesh;
	}
	break;
	default:
		cerr << "glTF2Maya: skipping '" << name() << "', it is not supported" << endl;
		break;
	}
}

ExportableNode::~ExportableNode()
{
}

std::unique_ptr<ExportableNode> ExportableNode::from(MDagPath dagPath, ExportableResources& usedShaderNames)
{
	MStatus status;

	MString name = dagPath.partialPathName(&status);
	THROW_ON_FAILURE(status);

	MObject mayaNode = dagPath.node(&status);
	if (mayaNode.isNull() || status.error())
	{
		cerr << "glTF2Maya: skipping '" << name.asChar() << "' as it is not a node" << endl;
		return nullptr;
	}

	return std::make_unique<ExportableNode>(dagPath, usedShaderNames);
}

std::unique_ptr<ExportableClip> ExportableNode::createClip(const std::string& clipName, const int frameCount)
{
	return std::make_unique<ExportableClip>(*this, clipName, frameCount);
}
