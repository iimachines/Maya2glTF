#pragma once

#include "PropAnimation.h"
#include "sceneTypes.h"
#include "ExportableNode.h"

class ExportableNode;
class ExportableMesh;
class NodeTransformCache;

class NodeAnimation
{
public:
	NodeAnimation(const ExportableNode& node, const ExportableFrames& frameTimes, const double scaleFactor);

	virtual ~NodeAnimation() = default;

	// Samples values at the current time
	virtual void sampleAt(const int relativeFrameIndex, NodeTransformCache& transformCache);

	virtual void exportTo(GLTF::Animation& glAnimation);

	const ExportableNode& node;
	const ExportableMesh* mesh;

private:
	const double m_scaleFactor;
	bool m_hasValidLocalTransforms;

	std::unique_ptr<PropAnimation> m_positions;
	std::unique_ptr<PropAnimation> m_rotations;
	std::unique_ptr<PropAnimation> m_scales;
	std::unique_ptr<PropAnimation> m_inverseParentScales;
	std::unique_ptr<PropAnimation> m_weights;

	void finish(GLTF::Animation& glAnimation,
		std::unique_ptr<PropAnimation>& animatedProp,
		const gsl::span<const float>& baseValues) const;

	template<int N>
	void finish(GLTF::Animation& glAnimation, std::unique_ptr<PropAnimation>& animatedProp, const float(&baseValues)[N])
	{
		finish(glAnimation, animatedProp, gsl::make_span(&baseValues[0], N));
	}

	DISALLOW_COPY_MOVE_ASSIGN(NodeAnimation);
};
