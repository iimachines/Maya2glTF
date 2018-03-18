#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "NodeAnimation.h"
#include "Transform.h"
#include "NodeHierarchy.h"
#include "Arguments.h"

ExportableNode::ExportableNode(
	NodeHierarchy& hierarchy,
	std::unique_ptr<ExportableNode>& owner,
	MDagPath dagPath)
	: ExportableObject(dagPath.node())
	, dagPath(dagPath)
	, scaleFactor(1)
{
	MStatus status;

	owner.reset(this);

	auto& resources = hierarchy.resources();
	auto& arguments = resources.arguments();

	// Remember scale factor
	scaleFactor = arguments.scaleFactor;

	// Get name
	glNode.name = dagPath.partialPathName(&status).asChar();
	THROW_ON_FAILURE(status);

	handleNameAssignment(resources, glNode);

	// Get parent
	const auto parentNode = hierarchy.getParent(this);
	parentDagPath = parentNode ? parentNode->dagPath : MDagPath();

	// Get transform
	const auto objectMatrix = Transform::getObjectSpaceMatrix(dagPath, parentDagPath);
	initialTransform = Transform::toTRS(objectMatrix, scaleFactor, glNode.name.c_str());
	THROW_ON_FAILURE(status);
	glNode.transform = &initialTransform;

	// Register as child
	if (parentNode)
	{
		parentNode->glNode.children.push_back(&glNode);
	}

	// Get mesh, but only if the node was selected.
	if (arguments.selection.hasItem(dagPath))
	{
		dagPath.extendToShape();

		switch (dagPath.apiType(&status))
		{
		case MFn::kMesh:
			m_mesh = std::make_unique<ExportableMesh>(hierarchy, dagPath);
			glNode.mesh = &m_mesh->glMesh;
			break;

		default:
			cerr << "glTF2Maya: skipping '" << name() << "', it is not a mesh" << endl;
			break;
		}
	}
}

ExportableNode::~ExportableNode() = default;

std::unique_ptr<NodeAnimation> ExportableNode::createAnimation(const int frameCount, const double scaleFactor)
{
	return std::make_unique<NodeAnimation>(*this, frameCount, scaleFactor);
}
