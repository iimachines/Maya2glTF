#pragma once

#include "ExportableFrames.h"
#include "accessors.h"
#include "macros.h"

class ExportableNode;

class PropAnimation {
  public:
    PropAnimation(const ExportableFrames &frames, const GLTF::Node &node, const GLTF::Animation::Path path, const size_t dimension,
                  size_t stepDetectSampleCount, const bool useFloatArray)
        : dimension(dimension), useFloatArray(useFloatArray), stepDetectSampleCount(stepDetectSampleCount), frames(frames) {

        componentValuesPerFrameTable.resize(stepDetectSampleCount);
        for (auto superSample = 0; superSample < stepDetectSampleCount; ++superSample) {
            componentValuesPerFrameTable[superSample].reserve(frames.count * dimension);
        }

        glTarget.node = &const_cast<GLTF::Node &>(node);
        glTarget.path = path;

        glChannel.sampler = &glSampler;
        glChannel.target = &glTarget;
    }

    ~PropAnimation() = default;

    const size_t dimension;
    const bool useFloatArray;
    const size_t stepDetectSampleCount;
    const ExportableFrames &frames;

    // For each step-detection super-sampling frame, a vector of component values
    std::vector<std::vector<float>> componentValuesPerFrameTable;

    GLTF::Animation::Channel glChannel;
    GLTF::Animation::Sampler glSampler;
    GLTF::Animation::Channel::Target glTarget;

    template <std::ptrdiff_t Extent> void append(const gsl::span<const float, Extent> &components, size_t superSample) {
        std::copy(components.begin(), components.end(), std::back_inserter(componentValuesPerFrameTable.at(superSample)));
    }

    void appendQuaternion(const gsl::span<const float, 4> &q, int superSample) {
        auto &componentValuesPerFrame = componentValuesPerFrameTable.at(superSample);

        const auto index = componentValuesPerFrame.size();
        if (index == 0) {
            append(q, superSample);
        } else {
            auto x0 = componentValuesPerFrame[index - 4];
            auto y0 = componentValuesPerFrame[index - 3];
            auto z0 = componentValuesPerFrame[index - 2];
            auto w0 = componentValuesPerFrame[index - 1];

            auto x1 = q[0];
            auto y1 = q[1];
            auto z1 = q[2];
            auto w1 = q[3];

            // Check if the negative quaternion is a closer.
            auto dp = (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1) + (z0 - z1) * (z0 - z1) + (w0 - w1) * (w0 - w1);
            auto dn = (x0 + x1) * (x0 + x1) + (y0 + y1) * (y0 + y1) + (z0 + z1) * (z0 + z1) + (w0 + w1) * (w0 + w1);

            if (dn < dp) {
                x1 = -x1;
                y1 = -y1;
                z1 = -z1;
                w1 = -w1;
            }

            componentValuesPerFrame.push_back(x1);
            componentValuesPerFrame.push_back(y1);
            componentValuesPerFrame.push_back(z1);
            componentValuesPerFrame.push_back(w1);
        }
    }

    void finish(const std::string &name, const bool useSingleKey, const char *interpolation) {
        glSampler.interpolation = interpolation;

        if (!m_outputs) {
            auto &componentValuesPerFrame = componentValuesPerFrameTable.at(0);

            if (useSingleKey) {
                componentValuesPerFrame.resize(dimension);
                glSampler.input = frames.glInput0();
            } else {
                glSampler.input = frames.glInputs();
            }

            if (stepDetectSampleCount > 1 && !useSingleKey) {
                // Remove all
            }

            m_outputs = contiguousChannelAccessor(name, span(componentValuesPerFrame), useFloatArray ? 1 : dimension);

            glSampler.output = m_outputs.get();

            // A channel cannot have a name according to the spec.
            // glChannel.name = name;
        }
    }

private:
    std::unique_ptr<GLTF::Accessor> m_outputs;

    DISALLOW_COPY_MOVE_ASSIGN(PropAnimation);
};
