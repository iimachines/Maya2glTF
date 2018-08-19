#include "externals.h"
#include "NodeAnimation.h"
#include "ExportableNode.h"
#include "ExportableMesh.h"
#include "Transform.h"
#include "OutputStreamsPatch.h"

NodeAnimation::NodeAnimation(
	const ExportableNode& node,
	const ExportableFrames& frames,
	const double scaleFactor)
	: node(node)
	, mesh(node.mesh())
	, m_scaleFactor(scaleFactor)
{
	auto& sNode = node.glSecondaryNode();
	auto& pNode = node.glPrimaryNode();

	m_invalidLocalTransformTimes.reserve(10);

	switch (node.transformKind)
	{
	case TransformKind::Simple: 
		m_positions = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::TRANSLATION, 3, false);
		m_rotations = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::ROTATION, 4, false);
		m_scales = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::SCALE, 3, false);
		break;
	case TransformKind::ComplexJoint:
		m_positions = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::TRANSLATION, 3, false);
		m_rotations = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::ROTATION, 4, false);
		m_scales = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::SCALE, 3, false);
		m_correctors = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::SCALE, 3, false);
		break;

	case TransformKind::ComplexTransform:
		m_positions = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::TRANSLATION, 3, false);
		m_rotations = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::ROTATION, 4, false);
		m_scales = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::SCALE, 3, false);
		m_correctors = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::TRANSLATION, 3, false);
		break;

	default: 
		assert(false);
		break;
	}

	if (mesh)
	{
		m_weights = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::WEIGHTS, mesh->blendShapeCount(), true);
	}
}

void NodeAnimation::sampleAt(const MTime& absoluteTime, const int frameIndex, NodeTransformCache& transformCache)
{
	auto& transformState = transformCache.getTransform(&node, m_scaleFactor);
	auto& pTRS = transformState.primaryTRS();
	auto& sTRS = transformState.secondaryTRS();

	if (!transformState.hasValidLocalTransforms && m_invalidLocalTransformTimes.size() < m_invalidLocalTransformTimes.capacity())
	{
		m_invalidLocalTransformTimes.emplace_back(absoluteTime);
	}

	switch (node.transformKind)
	{
	case TransformKind::Simple:
		m_positions->append(gsl::make_span(pTRS.translation));
		m_rotations->append(gsl::make_span(pTRS.rotation));
		m_scales->append(gsl::make_span(pTRS.scale));
		break;
	case TransformKind::ComplexJoint:
		m_positions->append(gsl::make_span(sTRS.translation));
		m_rotations->append(gsl::make_span(pTRS.rotation));
		m_scales->append(gsl::make_span(pTRS.scale));
		m_correctors->append(gsl::make_span(sTRS.scale));
		break;

	case TransformKind::ComplexTransform:
		m_positions->append(gsl::make_span(sTRS.translation));
		m_rotations->append(gsl::make_span(sTRS.rotation));
		m_scales->append(gsl::make_span(sTRS.scale));
		m_correctors->append(gsl::make_span(pTRS.translation));
		break;

	default:
		assert(false);
		break;
	}

	if (mesh)
	{
		const auto weightCount = mesh->blendShapeCount();
		if (weightCount)
		{
			auto weights = mesh->currentWeights();
			assert(weights.size() == weightCount);
			m_weights->append(span(weights));
		}
	}
}

void NodeAnimation::exportTo(GLTF::Animation& glAnimation)
{
	if (!m_invalidLocalTransformTimes.empty())
	{
		// TODO: Use SVG to decompose the 3x3 matrix into a product of rotation and scale matrices.
		cerr << prefix << "WARNING: node '" << node.name() << "' has animated transforms that are not representable by glTF! Skewing is not supported, use 3 nodes to simulate this" << endl;
		cerr << prefix << "The first invalid transforms were found at times: ";
		for (auto& time : m_invalidLocalTransformTimes)
			cerr << time << " ";
		cerr << endl;
	}

	// Now create the glTF animations, but only for those props that animate
	auto& pTRS = node.initialTransformState.primaryTRS();
	auto& sTRS = node.initialTransformState.secondaryTRS();

	switch (node.transformKind)
	{
	case TransformKind::Simple:
		finish(glAnimation, m_positions, pTRS.translation);
		finish(glAnimation, m_rotations, pTRS.rotation);
		finish(glAnimation, m_scales, pTRS.scale);
		break;
	case TransformKind::ComplexJoint:
		finish(glAnimation, m_positions, sTRS.translation);
		finish(glAnimation, m_rotations, pTRS.rotation);
		finish(glAnimation, m_scales, pTRS.scale);
		finish(glAnimation, m_correctors, sTRS.scale);
		break;

	case TransformKind::ComplexTransform:
		finish(glAnimation, m_positions, sTRS.translation);
		finish(glAnimation, m_rotations, sTRS.rotation);
		finish(glAnimation, m_scales, sTRS.scale);
		finish(glAnimation, m_correctors, pTRS.translation);
		break;

	default:
		assert(false);
		break;
	}

	if (mesh)
	{
		const auto initialWeights = mesh->initialWeights();
		finish(glAnimation, m_weights, initialWeights);
	}
}

void NodeAnimation::finish(
	GLTF::Animation& glAnimation, 
	std::unique_ptr<PropAnimation>& animatedProp,
    const gsl::span<const float>& baseValues) const
{
	const auto dimension = animatedProp->dimension;
	assert(dimension == baseValues.size());

	auto& componentValues = animatedProp->componentValuesPerFrame;

	bool isFrozen = true;

	for (size_t offset = 0; offset < componentValues.size() && isFrozen; offset += dimension)
	{
		for (size_t index = 0; index < dimension && isFrozen; ++index)
		{
			isFrozen = std::abs(baseValues[index] - componentValues[offset + index]) < 1e-9;
		}
	}

	if (isFrozen)
	{
		animatedProp.release();
	}
	else
	{
		animatedProp->finish(glAnimation.name + "_outputs");
		glAnimation.channels.push_back(&animatedProp->glChannel);
	}
}

