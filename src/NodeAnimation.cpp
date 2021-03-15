#include "externals.h"

#include "ExportableMesh.h"
#include "ExportableNode.h"
#include "NodeAnimation.h"
#include "OutputStreamsPatch.h"
#include "Transform.h"

NodeAnimation::NodeAnimation(const ExportableNode &node, const ExportableFrames &frames, const double scaleFactor, const Arguments &arguments)
    : node(node), mesh(node.mesh()), m_scaleFactor(scaleFactor), m_blendShapeCount(mesh ? mesh->blendShapeCount() : 0), m_arguments(arguments) {
    auto &sNode = node.glSecondaryNode();
    auto &pNode = node.glPrimaryNode();

    m_invalidLocalTransformTimes.reserve(10);

    const size_t detectStepSampleCount = m_arguments.getStepDetectSampleCount();

    switch (node.transformKind) {
    case TransformKind::Simple:
        m_positions = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::TRANSLATION, 3, detectStepSampleCount, false);
        m_rotations = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::ROTATION, 4, detectStepSampleCount, false);
        m_scales = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::SCALE, 3, detectStepSampleCount, false);
        break;
    case TransformKind::ComplexJoint:
        m_positions = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::TRANSLATION, 3, detectStepSampleCount, false);
        m_rotations = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::ROTATION, 4, detectStepSampleCount, false);
        m_scales = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::SCALE, 3, detectStepSampleCount, false);

        m_correctors = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::SCALE, 3, detectStepSampleCount, false);

        if (m_arguments.forceAnimationChannels) {
            m_dummyProps1 = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::TRANSLATION, 3, detectStepSampleCount, false);
            m_dummyProps2 = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::ROTATION, 4, detectStepSampleCount, false);
        }
        break;

    case TransformKind::ComplexTransform:
        m_positions = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::TRANSLATION, 3, detectStepSampleCount, false);
        m_rotations = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::ROTATION, 4, detectStepSampleCount, false);
        m_scales = std::make_unique<PropAnimation>(frames, sNode, GLTF::Animation::Path::SCALE, 3, detectStepSampleCount, false);

        m_correctors = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::TRANSLATION, 3, detectStepSampleCount, false);

        if (m_arguments.forceAnimationChannels) {
            m_dummyProps1 = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::SCALE, 3, detectStepSampleCount, false);
            m_dummyProps2 = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::ROTATION, 4, detectStepSampleCount, false);
        }
        break;

    default:
        assert(false);
        break;
    }

    if (m_blendShapeCount > 0) {
        m_weights = std::make_unique<PropAnimation>(frames, pNode, GLTF::Animation::Path::WEIGHTS, m_blendShapeCount, detectStepSampleCount, true);
    }
}

void NodeAnimation::sampleAt(const MTime &absoluteTime, const int frameIndex, const int superSampleIndex, NodeTransformCache &transformCache) {
    auto &transformState = transformCache.getTransform(&node, m_scaleFactor);
    auto &pTRS = transformState.primaryTRS();
    auto &sTRS = transformState.secondaryTRS();

    if (transformState.maxNonOrthogonality > MAX_NON_ORTHOGONALITY && m_invalidLocalTransformTimes.size() < m_invalidLocalTransformTimes.capacity()) {
        m_maxNonOrthogonality = std::max(m_maxNonOrthogonality, transformState.maxNonOrthogonality);
        m_invalidLocalTransformTimes.emplace_back(absoluteTime);
    }

    switch (node.transformKind) {
    case TransformKind::Simple:
        m_positions->append(gsl::make_span(pTRS.translation), superSampleIndex);
        m_rotations->appendQuaternion(gsl::make_span(pTRS.rotation), superSampleIndex);
        m_scales->append(gsl::make_span(pTRS.scale), superSampleIndex);
        break;
    case TransformKind::ComplexJoint:
        m_positions->append(gsl::make_span(sTRS.translation), superSampleIndex);
        m_rotations->appendQuaternion(gsl::make_span(pTRS.rotation), superSampleIndex);
        m_scales->append(gsl::make_span(pTRS.scale), superSampleIndex);

        m_correctors->append(gsl::make_span(sTRS.scale), superSampleIndex);

        if (m_arguments.forceAnimationChannels) {
            m_dummyProps1->append(gsl::make_span(pTRS.translation), superSampleIndex);
            m_dummyProps2->appendQuaternion(gsl::make_span(sTRS.rotation), superSampleIndex);
        }
        break;

    case TransformKind::ComplexTransform:
        m_positions->append(gsl::make_span(sTRS.translation), superSampleIndex);
        m_rotations->appendQuaternion(gsl::make_span(sTRS.rotation), superSampleIndex);
        m_scales->append(gsl::make_span(sTRS.scale), superSampleIndex);

        m_correctors->append(gsl::make_span(pTRS.translation), superSampleIndex);

        if (m_arguments.forceAnimationChannels) {
            m_dummyProps1->append(gsl::make_span(pTRS.scale), superSampleIndex);
            m_dummyProps2->appendQuaternion(gsl::make_span(pTRS.rotation), superSampleIndex);
        }
        break;

    default:
        assert(false);
        break;
    }

    if (m_blendShapeCount) {
        auto weights = mesh->currentWeights();
        assert(weights.size() == m_blendShapeCount);
        m_weights->append(span(weights), superSampleIndex);
    }
}

void NodeAnimation::exportTo(GLTF::Animation &glAnimation) {

    if (!m_invalidLocalTransformTimes.empty()) {
        // TODO: Use SVG to decompose the 3x3 matrix into a product of rotation
        // and scale matrices.
        cerr << prefix << "WARNING: node '" << node.name()
             << "' has animated transforms that are not representable by glTF! "
                "Skewing is not supported, use 3 nodes to simulate this. "
                "Largest deviation = "
             << std::fixed << std::setprecision(2) << m_maxNonOrthogonality * 100 << "%" << endl;

        cerr << prefix << "The first invalid transforms were found at times: ";
        for (auto &time : m_invalidLocalTransformTimes)
            cerr << time << " ";
        cerr << endl;
    }

    // Now create the glTF animations, but only for those props that animate
    auto &pTRS = node.initialTransformState.primaryTRS();
    auto &sTRS = node.initialTransformState.secondaryTRS();

    switch (node.transformKind) {
    case TransformKind::Simple:
        finish(glAnimation, "T", m_positions, m_arguments.constantTranslationThreshold, pTRS.translation);
        finish(glAnimation, "R", m_rotations, m_arguments.constantRotationThreshold, pTRS.rotation);
        finish(glAnimation, "S", m_scales, m_arguments.constantScalingThreshold, pTRS.scale);
        break;
    case TransformKind::ComplexJoint:
        finish(glAnimation, "T", m_positions, m_arguments.constantTranslationThreshold, sTRS.translation);
        finish(glAnimation, "R", m_rotations, m_arguments.constantRotationThreshold, pTRS.rotation);
        finish(glAnimation, "S", m_scales, m_arguments.constantScalingThreshold, pTRS.scale);

        finish(glAnimation, "C", m_correctors, m_arguments.constantScalingThreshold, sTRS.scale);

        if (m_arguments.forceAnimationChannels) {
            finish(glAnimation, "DT", m_dummyProps1, 0, pTRS.translation);
            finish(glAnimation, "DR", m_dummyProps2, 0, sTRS.rotation);
        }
        break;

    case TransformKind::ComplexTransform:
        finish(glAnimation, "T", m_positions, m_arguments.constantTranslationThreshold, sTRS.translation);
        finish(glAnimation, "R", m_rotations, m_arguments.constantRotationThreshold, sTRS.rotation);
        finish(glAnimation, "S", m_scales, m_arguments.constantScalingThreshold, sTRS.scale);

        finish(glAnimation, "C", m_correctors, m_arguments.constantScalingThreshold, pTRS.translation);

        if (m_arguments.forceAnimationChannels) {
            finish(glAnimation, "DS", m_dummyProps1, 0, pTRS.scale);
            finish(glAnimation, "DR", m_dummyProps2, 0, pTRS.rotation);
        }
        break;

    default:
        assert(false);
        break;
    }

    if (m_blendShapeCount) {
        const auto initialWeights = mesh->initialWeights();
        assert(initialWeights.size() == m_blendShapeCount);
        finish(glAnimation, "W", m_weights, m_arguments.constantWeightsThreshold, initialWeights);
    }
}

void NodeAnimation::finish(GLTF::Animation &glAnimation, const char *propName, std::unique_ptr<PropAnimation> &animatedProp,
    double constantThreshold, const gsl::span<const float> &baseValues) const {
    const auto dimension = animatedProp->dimension;

    if (dimension) {
        assert(dimension == baseValues.size());

        const size_t detectStepSampleCount = m_arguments.getStepDetectSampleCount();

        auto &componentValues = animatedProp->componentValuesPerFrameTable.at(0);

        // Check if all samples are constant. In that case, we drop the animation, unless it is forced
        bool isConstant = true;
        for (size_t offset = 0; offset < componentValues.size() && isConstant; offset += dimension) {
            for (size_t axis = 0; axis < dimension && isConstant; ++axis) {
                isConstant = std::abs(baseValues[axis] - componentValues[offset + axis]) < constantThreshold;
            }
        }

        if (isConstant && !m_arguments.forceAnimationSampling && !m_arguments.forceAnimationChannels) {
            // All animation frames are the same as the scene, to need to animate the prop.
            animatedProp.release();
        } else {
            const auto useSingleKey = isConstant && !m_arguments.forceAnimationSampling;
            auto interpolation = "LINEAR";

            if (!useSingleKey && detectStepSampleCount > 1) {
                // Check if STEP animation can be used for this channel.
                // TODO: Split into multiple parts!
                auto canUseStep = true;
                for (size_t offset = 0; offset < componentValues.size() && canUseStep; offset += dimension) {
                    const auto* startValues = &componentValues[offset];
                    for (size_t superSample = 1; superSample < detectStepSampleCount; ++superSample) {
                        auto &stepComponentValues = animatedProp->componentValuesPerFrameTable.at(superSample);
                        for (size_t axis = 0; axis < dimension; ++axis) {
                            canUseStep = std::abs(startValues[axis] - stepComponentValues[offset + axis]) < constantThreshold;
                        }
                    }
                }

                if (canUseStep) {
                    std::cout << prefix << "Using STEP interpolation for channel " << node.name() << "/" << propName << std::endl;
                    interpolation = "STEP";
                }
            }

            // TODO: Apply a curve simplifier.
            animatedProp->finish(m_arguments.disableNameAssignment ? "" : node.name() + "/anim/" + glAnimation.name + "/" + propName, useSingleKey, interpolation);
            glAnimation.channels.push_back(&animatedProp->glChannel);
        }
    }
}
