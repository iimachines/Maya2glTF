#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "NodeAnimation.h"
#include "Transform.h"
#include "ExportableScene.h"
#include "Arguments.h"
#include "DagHelper.h"

ExportableNode::ExportableNode(
	ExportableScene& scene,
	NodeTransformCache& transformCache,
	std::unique_ptr<ExportableNode>& owner,
	MDagPath dagPath)
	: ExportableObject(dagPath.node())
	, dagPath(dagPath)
	, hasSegmentScaleCompensation(false)
	, scaleFactor(1)
	, parentNode(nullptr)
{
	MStatus status;

	owner.reset(this);

	auto& resources = scene.resources();
	auto& args = resources.arguments();

	// Is this a joint with segment scale compensation? (the default in Maya)
	bool maybeSegmentScaleCompensation = false;
	DagHelper::getPlugValue(obj, "segmentScaleCompensate", maybeSegmentScaleCompensation);

	// Remember scale factor
	scaleFactor = args.scaleFactor;

	// Get name
	const auto name = dagPath.partialPathName(&status);
	THROW_ON_FAILURE(status);

	// Get parent
	parentNode = scene.getParent(this);

	// A root joint never has segment scale compensation, since the parent is the world.
	hasSegmentScaleCompensation =
		maybeSegmentScaleCompensation &&
		parentNode &&
		parentNode->obj.hasFn(MFn::kJoint) &&
		!args.ignoreSegmentScaleCompensation;

	// In the presence of segment scale compensation, 
	// parent.TRS <- child.TRS 
	// becomes
	// parent.TU <- parent.RS <- child.TU <- child.RS

	// TODO: Cleanup the segment scale compensation code
	auto& nodeTU = glNodeTU();
	auto& nodeRS = glNodeRS();

	args.assignName(nodeTU, name.asChar());

	if (hasSegmentScaleCompensation)
	{
		args.assignName(nodeRS, (name + "_SSC").asChar());
		nodeTU.children.emplace_back(&nodeRS);
	}

	if (parentNode)
	{
		// Register as child
		parentNode->glNodeRS().children.push_back(&nodeTU);
	}
	else
	{
		// Add root nodes to the scene
		scene.glScene.nodes.emplace_back(&nodeTU);
	}

	// Get transform
	initialTransformState = transformCache.getTransform(this, scaleFactor);
	m_glNodes[0].transform = &initialTransformState.localTransforms[0];
	m_glNodes[1].transform = &initialTransformState.localTransforms[1];

	if (!initialTransformState.hasValidLocalTransforms)
	{
		// TODO: Use SVG to decompose the 3x3 matrix into a product of rotation and scale matrices.
		cerr << prefix << "WARNING: node '" << name << "' has transforms that are not representable by glTF! Skewing is not supported, use 3 nodes to simulate this" << endl;
	}

	// Get mesh, but only if the node was selected.
	if (args.selection.hasItem(dagPath))
	{
		dagPath.extendToShape();

		if (dagPath.hasFn(MFn::kMesh)) 
		{
			m_mesh = std::make_unique<ExportableMesh>(scene, dagPath);
			nodeRS.mesh = &m_mesh->glMesh;

			// Link skin if mesh has skeleton
			if (m_mesh->glSkin.skeleton)
			{
				nodeRS.skin = &m_mesh->glSkin;
			}
		}
	}
}

ExportableNode::~ExportableNode() = default;

std::unique_ptr<NodeAnimation> ExportableNode::createAnimation(const ExportableFrames& frameTimes, const double scaleFactor)
{
	return std::make_unique<NodeAnimation>(*this, frameTimes, scaleFactor);
}
