#pragma once

#include "macros.h"
#include "accessors.h"

class ExportableNode;

template<typename T>
class PropAnimation
{
public:
	PropAnimation(GLTF::Accessor& timesPerFrame, const GLTF::Node& node, const GLTF::Animation::Path path, const char* interpolation = "LINEAR")
	{
		valuesPerFrame.reserve(timesPerFrame.count);

		glTarget.node = &const_cast<GLTF::Node&>(node);
		glTarget.path = path;

		glChannel.sampler = &glSampler;
		glChannel.target = &glTarget;

		glSampler.input = &timesPerFrame;
		glSampler.interpolation = interpolation;
	}

	std::vector<T> valuesPerFrame;

	GLTF::Animation::Channel glChannel;
	GLTF::Animation::Sampler glSampler;
	GLTF::Animation::Channel::Target glTarget;

	void finish()
	{
		if (!m_outputs)
		{
			// TODO: Allow passing name of node+path for debugging
			m_outputs = contiguousChannelAccessor(nullptr, span(valuesPerFrame));
		}

		glSampler.output = m_outputs.get();
	}

private:
	std::unique_ptr<GLTF::Accessor> m_outputs;

	DISALLOW_COPY_MOVE_ASSIGN(PropAnimation);
};
