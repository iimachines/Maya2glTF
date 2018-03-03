#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "NodeAnimation.h"
#include "Transform.h"
#include "Arguments.h"

ExportableNode::ExportableNode(MDagPath dagPath, ExportableResources& resources)
	: ExportableObject(dagPath.node())
	, dagPath(dagPath)
{
	CONSTRUCTOR_BEGIN();

	MStatus status;

	handleNameAssignment(resources, glNode);

	const auto objectMatrix = Transform::getObjectSpaceMatrix(dagPath);
	m_transform = Transform::toTRS(objectMatrix, resources.arguments().scaleFactor, dagPath.fullPathName(&status).asChar());
	THROW_ON_FAILURE(status);

	glNode.transform = &m_transform;

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

	CONSTRUCTOR_END();
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

std::unique_ptr<NodeAnimation> ExportableNode::createAnimation(const int frameCount, const double scaleFactor)
{
	return std::make_unique<NodeAnimation>(*this, frameCount, scaleFactor);
}
