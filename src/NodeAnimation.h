#pragma once

#include "ExportableNode.h"
#include "PropAnimation.h"
#include "Arguments.h"

class ExportableNode;
class ExportableMesh;
class NodeTransformCache;

class NodeAnimation {
  public:
    NodeAnimation(const ExportableNode &node, const ExportableFrames &frames, double scaleFactor, const Arguments &args);

    /** Consider a blend shape weight animation path as constant if all values are below this threshold */
    double constantWeightsThreshold = 1e-9;

    virtual ~NodeAnimation() = default;

    // Samples values at the current time
    void sampleAt(const MTime &absoluteTime, int relativeFrameIndex, NodeTransformCache &transformCache);

    void exportTo(GLTF::Animation &glAnimation);

    const ExportableNode &node;
    const ExportableMesh *mesh;

  private:
    const double m_scaleFactor;
    const size_t m_blendShapeCount;
    const Arguments &m_arguments;

    double m_maxNonOrthogonality = 0;
    std::vector<MTime> m_invalidLocalTransformTimes;

    std::unique_ptr<PropAnimation> m_positions;
    std::unique_ptr<PropAnimation> m_rotations;
    std::unique_ptr<PropAnimation> m_scales;

    // Either the inverse parent scales, or pivot offsets.
    std::unique_ptr<PropAnimation> m_correctors; 

    // Dummy constant channels for when animation channels are forced.
    std::unique_ptr<PropAnimation> m_dummyProps1; 
    std::unique_ptr<PropAnimation> m_dummyProps2;

    std::unique_ptr<PropAnimation> m_weights;

    void finish(GLTF::Animation &glAnimation, const char *propName, std::unique_ptr<PropAnimation> &animatedProp, double constantThreshold,
                int detectStepSampleCount, const gsl::span<const float> &baseValues) const;

    template <int N>
    void finish(GLTF::Animation &glAnimation, const char *propName, std::unique_ptr<PropAnimation> &animatedProp, 
        double constantThreshold, int detectStepSampleCount, const float (&baseValues)[N]) {
        finish(glAnimation, propName, animatedProp, constantThreshold, detectStepSampleCount, gsl::make_span(&baseValues[0], N));
    }

    DISALLOW_COPY_MOVE_ASSIGN(NodeAnimation);
};
