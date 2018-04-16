#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "NodeAnimation.h"
#include "Transform.h"
#include "ExportableScene.h"
#include "Arguments.h"

ExportableNode::ExportableNode(MDagPath dagPath)
	: ExportableObject(dagPath.node())
	, dagPath(dagPath)
	, scaleFactor(1)
{
}

void ExportableNode::load(ExportableScene& scene)
{
	MStatus status;

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
		MDagPath shapeDagPath = dagPath;
		status = shapeDagPath.extendToShape();

		if (status && shapeDagPath.hasFn(MFn::kMesh))
		{
			// The shape is a mesh
			meshDagPath = shapeDagPath;

			// We can only simulate a single pivot point, 
			// but Maya has both a rotation and scaling pivot, 
			// so warn the user if these are different.
			MDagPath parentDagPath = meshDagPath;
			status = parentDagPath.pop();
			THROW_ON_FAILURE(status);

			MFnTransform parentTransform(parentDagPath, &status);
			THROW_ON_FAILURE(status);

			const auto scalePivot = parentTransform.scalePivot(MSpace::kObject);
			const auto rotatePivot = parentTransform.rotatePivot(MSpace::kObject);

			if (scalePivot != rotatePivot)
			{
				MayaException::printError(formatted("Transform '%s' of mesh '%s' has different scaling and rotation pivots, this is not supported, ignoring scaling pivot!",
					parentDagPath.partialPathName().asChar(), meshDagPath.partialPathName().asChar()), MStatus::kNotImplemented);
			}

			pivotPoint = rotatePivot;

			if (pivotPoint != MPoint::origin)
			{
				cout << prefix << "Offseting all vertices of '" << meshDagPath.partialPathName() << "' around rotation pivot " << pivotPoint << endl;
			}

			MTransformationMatrix pivotTransformationMatrix;
			pivotTransformationMatrix.setTranslation(pivotPoint - MPoint::origin, MSpace::kObject);
			pivotTransform = pivotTransformationMatrix.asMatrix();
		}
	}

	// Get transform
	const auto objectMatrix = Transform::getObjectSpaceMatrix(pivotTransform, dagPath, parentDagPath);
	initialTransform = Transform::toTRS(objectMatrix, scaleFactor, name.asChar());
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
