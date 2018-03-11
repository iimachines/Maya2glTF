#pragma once

#include "PropAnimation.h"
#include "sceneTypes.h"

class ExportableNode;
class ExportableMesh;

class NodeAnimation
{
public:
	NodeAnimation(const ExportableNode& node, const int frameCount, const double scaleFactor);

	virtual ~NodeAnimation() = default;

	// Samples values at the current time
	virtual void sampleAt(const int relativeFrameIndex);

	virtual void exportTo(GLTF::Accessor& timesPerFrame, GLTF::Animation& glAnimation);

	const ExportableNode& node;
	const ExportableMesh* mesh;

private:
	const double m_scaleFactor;
	bool m_allOrthogonalAxes;
	std::vector<MMatrix> m_objectMatrices;
	std::vector<float> m_targetWeights;

	typedef PropAnimation AnimatedT;
	typedef PropAnimation AnimatedR;
	typedef PropAnimation AnimatedS;
	typedef PropAnimation AnimatedW;

	std::unique_ptr<AnimatedT> m_positions;
	std::unique_ptr<AnimatedR> m_rotations;
	std::unique_ptr<AnimatedS> m_scales;
	std::unique_ptr<AnimatedW> m_weights;

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
