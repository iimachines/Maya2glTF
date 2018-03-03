#pragma once

#include "PropAnimation.h"
#include "sceneTypes.h"

class ExportableNode;

class NodeAnimation
{
public:
	NodeAnimation(const ExportableNode& node, const int frameCount, const double scaleFactor);

	virtual ~NodeAnimation() = default;

	// Samples values at the current time
	virtual void sampleAt(const int relativeFrameIndex);

	virtual void exportTo(GLTF::Accessor& timesPerFrame, GLTF::Animation& glAnimation);

	const ExportableNode& node;

private:
	const double m_scaleFactor;
	bool m_allOrthogonalAxes;
	std::vector<MMatrix> m_objectMatrices;

	typedef PropAnimation<Position> AnimatedT;
	typedef PropAnimation<Rotation> AnimatedR;
	typedef PropAnimation<Scale> AnimatedS;

	std::unique_ptr<AnimatedT> m_positions;
	std::unique_ptr<AnimatedR> m_rotations;
	std::unique_ptr<AnimatedS> m_scales;

	template<typename T, int N>
	void finish(GLTF::Animation& glAnimation, std::unique_ptr<PropAnimation<T>>& animatedProp, const float (&baseValues)[N])
	{
		auto& values = animatedProp->valuesPerFrame;
		const bool isAnimated = std::any_of(values.begin(), values.end(), [baseValues](auto& value) 
		{
			for (int i = N; --i >= 0;)
			{
				if (std::abs(baseValues[i] - value[i]) > 1e-9)
					return true;
			}

			return false;
		});

		if (isAnimated)
		{
			animatedProp->finish();
			glAnimation.channels.push_back(&animatedProp->glChannel);
		}
		else
		{
			animatedProp.release();
		}
	}

	DISALLOW_COPY_AND_ASSIGN(NodeAnimation);
};
