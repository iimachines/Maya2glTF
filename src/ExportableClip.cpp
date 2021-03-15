#include "externals.h"

#include "ExportableClip.h"
#include "ExportableNode.h"
#include "progress.h"
#include "timeControl.h"

ExportableClip::ExportableClip(const Arguments &args, const AnimClipArg &clipArg, const ExportableScene &scene)
    : m_frames(args.makeName(clipArg.name + "/anim/frames"), clipArg.frameCount(), clipArg.framesPerSecond) {
    glAnimation.name = clipArg.name;

    const auto stepDetectSampleCount = args.getStepDetectSampleCount();
    const auto frameCount = m_frames.count;
    const auto scaleFactor = args.getBakeScaleFactor();

    auto &items = scene.table();

    m_nodeAnimations.reserve(items.size());

    for (auto &pair : items) {
        auto &node = pair.second;
        auto nodeAnimation = node->createAnimation(args, m_frames, scaleFactor);
        if (nodeAnimation) {
            m_nodeAnimations.emplace_back(std::move(nodeAnimation));
        }
    }

    const auto superSampleFrameRate = stepDetectSampleCount * clipArg.framesPerSecond;

    // To make sure Maya never rounds to just before a frame, we add half the smallest time step. Need to detect step interpolation
    const double mayaTimeEpsilon = 0.5 / 141120000;

    for (size_t relativeFrameIndex = 0; relativeFrameIndex < frameCount; ++relativeFrameIndex) {
        for (size_t superSampleIndex = 0; superSampleIndex < stepDetectSampleCount; ++superSampleIndex) {
            const double relativeFrameTime = (relativeFrameIndex * stepDetectSampleCount + superSampleIndex) / superSampleFrameRate + mayaTimeEpsilon;
            const MTime absoluteFrameTime = clipArg.startTime + MTime(relativeFrameTime, MTime::kSeconds);
            setCurrentTime(absoluteFrameTime, args.redrawViewport && superSampleIndex == 0);
            // const auto absoluteFrameTimeDebug = MAnimControl::currentTime().as(MTime::k24FPS);

            NodeTransformCache transformCache;
            for (auto &nodeAnimation : m_nodeAnimations) {
                nodeAnimation->sampleAt(absoluteFrameTime, relativeFrameIndex, superSampleIndex, transformCache);
            }
        }

        if (relativeFrameIndex % checkProgressFrameInterval == checkProgressFrameInterval - 1) {
            uiAdvanceProgress("exporting clip '" + clipArg.name + formatted("' %d%%", relativeFrameIndex * 100 / frameCount));
        }
    }

    for (auto &nodeAnimation : m_nodeAnimations) {
        nodeAnimation->exportTo(glAnimation);
    }
}

ExportableClip::~ExportableClip() = default;
