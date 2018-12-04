#pragma once

#include "macros.h"
#include "accessors.h"
#include "ExportableFrames.h"

class ExportableNode;

class PropAnimation
{
public:
	PropAnimation(
		const ExportableFrames& frames, 
		const GLTF::Node& node, 
		const GLTF::Animation::Path path, 
		const size_t dimension, 
		const bool useFloatArray, 
		const char* interpolation = "LINEAR")
		: dimension(dimension)
		, useFloatArray(useFloatArray)
	{
		componentValuesPerFrame.reserve(frames.count * dimension);

		glTarget.node = &const_cast<GLTF::Node&>(node);
		glTarget.path = path;

		glChannel.sampler = &glSampler;
		glChannel.target = &glTarget;

		glSampler.input = const_cast<GLTF::Accessor*>(frames.glInputs.get());
		glSampler.interpolation = interpolation;
	}

	~PropAnimation() = default;

	const size_t dimension;
	const bool useFloatArray;

	std::vector<float> componentValuesPerFrame;

	GLTF::Animation::Channel glChannel;
	GLTF::Animation::Sampler glSampler;
	GLTF::Animation::Channel::Target glTarget;

	template<std::ptrdiff_t Extent>
	void append(const gsl::span<const float, Extent>& components)
	{
		std::copy(components.begin(), components.end(), std::back_inserter(componentValuesPerFrame));
	}

	void finish(const std::string& outputsName)
	{
		if (!m_outputs)
		{
			m_outputs = useFloatArray 
				? contiguousChannelAccessor(outputsName, reinterpret_span<float>(componentValuesPerFrame), 1)
				: contiguousChannelAccessor(outputsName, span(componentValuesPerFrame), dimension);
		}

		glSampler.output = m_outputs.get();
	}

    void getAllAccessors(std::vector<GLTF::Accessor*>& accessors) const
	{
        if (m_outputs && m_outputs->count > 0)
        {
            accessors.emplace_back(m_outputs.get());
        }
	}

private:
	std::unique_ptr<GLTF::Accessor> m_outputs;

	DISALLOW_COPY_MOVE_ASSIGN(PropAnimation);
};
