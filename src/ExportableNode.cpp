#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "NodeAnimation.h"
#include "Transform.h"
#include "NodeHierarchy.h"
#include "Arguments.h"

ExportableNode::ExportableNode(MDagPath dagPath, ExportableResources& resources)
	: ExportableObject(dagPath.node())
	, dagPath(dagPath)
	, scaleFactor(resources.arguments().scaleFactor)
{
	MStatus status;

	glNode.name = dagPath.partialPathName(&status).asChar();
	THROW_ON_FAILURE(status);

	handleNameAssignment(resources, glNode);

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

ExportableNode::~ExportableNode() = default;

std::unique_ptr<ExportableNode> ExportableNode::from(MDagPath dagPath, ExportableResources& usedShaderNames)
{
	MStatus status;

	MObject mayaNode = dagPath.node(&status);
	if (mayaNode.isNull() || status.error())
	{
		MString name = dagPath.fullPathName(&status);
		THROW_ON_FAILURE(status);

		cerr << "glTF2Maya: skipping '" << name.asChar() << "' as it is not a node" << endl;
		return nullptr;
	}

	return std::make_unique<ExportableNode>(dagPath, usedShaderNames);
}

void ExportableNode::connectToHierarchy(const NodeHierarchy& dagNodeTable)
{
	const auto parentNode = dagNodeTable.parentOf(this);
	parentDagPath = parentNode ? parentNode->dagPath : MDagPath();

	const auto objectMatrix = Transform::getObjectSpaceMatrix(dagPath, parentDagPath);

	MStatus status;
	initialTransform = Transform::toTRS(objectMatrix, scaleFactor, glNode.name.c_str());
	THROW_ON_FAILURE(status);

	glNode.transform = &initialTransform;

	if (parentNode)
	{
		parentNode->glNode.children.push_back(&glNode);
	}
}

std::unique_ptr<NodeAnimation> ExportableNode::createAnimation(const int frameCount, const double scaleFactor)
{
	return std::make_unique<NodeAnimation>(*this, frameCount, scaleFactor);
}
