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
	, m_hasValidLocalTransforms(true)
{
	auto& glNodeTiS = node.glNodeTU();
	auto& glNodeRs = node.glNodeRS();

	m_positions = std::make_unique<PropAnimation>(frames, glNodeTiS, GLTF::Animation::Path::TRANSLATION, 3, false);
	m_rotations = std::make_unique<PropAnimation>(frames, glNodeRs, GLTF::Animation::Path::ROTATION, 4, false);
	m_scales = std::make_unique<PropAnimation>(frames, glNodeRs, GLTF::Animation::Path::SCALE, 3, false);

	if (node.hasSegmentScaleCompensation)
	{
		m_inverseParentScales = std::make_unique<PropAnimation>(frames, glNodeTiS, GLTF::Animation::Path::SCALE, 3, false);
	}

	if (mesh)
	{
		m_weights = std::make_unique<PropAnimation>(frames, glNodeTiS, GLTF::Animation::Path::WEIGHTS, mesh->blendShapeCount(), true);
	}
}

void NodeAnimation::sampleAt(const int frameIndex, NodeTransformCache& transformCache)
{
	auto& transformState = transformCache.getTransform(&node, m_scaleFactor);
	auto& localTransformRS = transformState.localTransformRS();
	auto& localTransformTU = transformState.localTransformTU();

	m_hasValidLocalTransforms &= transformState.hasValidLocalTransforms;
	m_positions->append(gsl::make_span(localTransformTU.translation));
	m_rotations->append(gsl::make_span(localTransformRS.rotation));
	m_scales->append(gsl::make_span(localTransformRS.scale));

	if (node.hasSegmentScaleCompensation)
	{
		m_inverseParentScales->append(gsl::make_span(localTransformRS.scale));
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
	if (!m_hasValidLocalTransforms)
	{
		// TODO: Use SVG to decompose the 3x3 matrix into a product of rotation and scale matrices.
		cerr << prefix << "WARNING: node '" << node.name() << "' has transforms that are not representable by glTF! Skewing is not supported, use 3 nodes to simulate this" << endl;
	}

	// Now create the glTF animations, but only for those props that animate
	auto& localTransformRS = node.initialTransformState.localTransformRS();
	auto& localTransformTU = node.initialTransformState.localTransformTU();

	finish(glAnimation, m_positions, localTransformTU.translation);
	finish(glAnimation, m_rotations, localTransformRS.rotation);
	finish(glAnimation, m_scales, localTransformRS.scale);

	if (node.hasSegmentScaleCompensation)
	{
		finish(glAnimation, m_inverseParentScales, localTransformTU.scale);
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
