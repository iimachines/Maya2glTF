#pragma once

#include "ExportableFrames.h"
#include "accessors.h"
#include "macros.h"

class ExportableNode;

class PropAnimation {
  public:
    PropAnimation(const ExportableFrames &frames, const GLTF::Node &node, const GLTF::Animation::Path path,
                  const size_t dimension, const bool useFloatArray, const char *interpolation = "LINEAR")
        : dimension(dimension), useFloatArray(useFloatArray), frames(frames) {
        componentValuesPerFrame.reserve(frames.count * dimension);

        glTarget.node = &const_cast<GLTF::Node &>(node);
        glTarget.path = path;

        glChannel.sampler = &glSampler;
        glChannel.target = &glTarget;

        glSampler.interpolation = interpolation;
    }

    ~PropAnimation() = default;

    const size_t dimension;
    const bool useFloatArray;
    const ExportableFrames &frames;

    std::vector<float> componentValuesPerFrame;

    GLTF::Animation::Channel glChannel;
    GLTF::Animation::Sampler glSampler;
    GLTF::Animation::Channel::Target glTarget;

    template <std::ptrdiff_t Extent> void append(const gsl::span<const float, Extent> &components) {
        std::copy(components.begin(), components.end(), std::back_inserter(componentValuesPerFrame));
    }

    void appendQuaternion(const gsl::span<const float, 4>& q) {
        const auto index = componentValuesPerFrame.size();
        if (index == 0) {
            append(q);
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

    void finish(const std::string &name, const bool useSingleKey) {
        if (!m_outputs) {
            if (useSingleKey) {
                componentValuesPerFrame.resize(dimension);
                glSampler.input = frames.glInput0();
            } else {
                glSampler.input = frames.glInputs();
            }

            m_outputs = contiguousChannelAccessor(name, span(componentValuesPerFrame), useFloatArray ? 1 : dimension);

            glSampler.output = m_outputs.get();

            // A channel cannot have a name according to the spec.
            // glChannel.name = name;
        }
    }

    void getAllAccessors(std::vector<GLTF::Accessor *> &accessors) const {
        if (m_outputs && m_outputs->count > 0) {
            accessors.emplace_back(m_outputs.get());
        }
    }

  private:
    std::unique_ptr<GLTF::Accessor> m_outputs;

    DISALLOW_COPY_MOVE_ASSIGN(PropAnimation);
};
