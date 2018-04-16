#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "NodeAnimation.h"
#include "Transform.h"
#include "ExportableScene.h"
#include "Arguments.h"

ExportableNode::ExportableNode(
	ExportableScene& scene,
	std::unique_ptr<ExportableNode>& owner,
	MDagPath dagPath)
	: ExportableObject(dagPath.node())
	, dagPath(dagPath)
	, scaleFactor(1)
{
	MStatus status;

	owner.reset(this);

	auto& resources = scene.resources();
	auto& args = resources.arguments();

	// Remember scale factor
	scaleFactor = args.scaleFactor;

	// Get name
	const auto name = dagPath.partialPathName(&status);
	THROW_ON_FAILURE(status);
	args.assignName(glNode, name.asChar());

	// Get parent
	const auto parentNode = scene.getParent(this);
	if (parentNode)
	{
		parentDagPath = parentNode->dagPath;
	}
	else
	{
		// Add root nodes to the scene
		scene.glScene.nodes.emplace_back(&glNode);
	}

	// Get mesh, but only if the node was selected.
	MDagPath meshDagPath;

	if (args.selection.hasItem(dagPath))
	{
		meshDagPath = dagPath;
		status = meshDagPath.extendToShape();

		if (status && meshDagPath.hasFn(MFn::kMesh))
		{
			// We can only simulate a single pivot point, but Maya has both a rotation and scaling pivot, so warn the user if needed.
			MDagPath parentDagPath = meshDagPath;
			THROW_ON_FAILURE(status);
			parentDagPath.pop();

			MFnTransform parentTransform(parentDagPath, &status);
			THROW_ON_FAILURE(status);

			const auto scalePivot = parentTransform.scalePivot(MSpace::kObject);
			const auto rotatePivot = parentTransform.rotatePivot(MSpace::kObject);

			if (scalePivot != rotatePivot)
			{
				MayaException::printError(formatted("Transform '%s' of mesh '%s' has a different scaling and rotation pivot, this is not supported!",
					parentDagPath.partialPathName().asChar(), dagPath.partialPathName().asChar()), MStatus::kNotImplemented);
			}

			pivotPoint = rotatePivot;

			if (pivotPoint != MPoint::origin)
			{
				cout << prefix << "Offseting all vertices of '" << dagPath.partialPathName() << "' around rotation pivot " << pivotPoint << endl;
			}

			MTransformationMatrix pivotTransformationMatrix;
			pivotTransformationMatrix.setTranslation(pivotPoint - MPoint::origin, MSpace::kObject);
			pivotTransform = pivotTransformationMatrix.asMatrix();
		}
	}

	// Get transform
	const auto objectMatrix = Transform::getObjectSpaceMatrix(pivotTransform, dagPath, parentDagPath);
	initialTransform = Transform::toTRS(objectMatrix, scaleFactor, name.asChar());
	THROW_ON_FAILURE(status);
	glNode.transform = &initialTransform;

	// Register as child
	if (parentNode)
	{
		parentNode->glNode.children.push_back(&glNode);
	}

	// Create mesh, if any
	if (meshDagPath.isValid(&status) && status)
	{
		m_mesh = std::make_unique<ExportableMesh>(scene, *this, meshDagPath);
		m_mesh->setupNode(glNode);
	}
}

ExportableNode::~ExportableNode() = default;

std::unique_ptr<NodeAnimation> ExportableNode::createAnimation(const int frameCount, const double scaleFactor)
{
	return std::make_unique<NodeAnimation>(*this, frameCount, scaleFactor);
}
