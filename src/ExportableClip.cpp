#include "ExportableClip.h"
#include "ExportableNode.h"
#include "externals.h"
#include "progress.h"
#include "timeControl.h"

ExportableClip::ExportableClip(const Arguments &args,
                               const AnimClipArg &clipArg,
                               const ExportableScene &scene)
    : m_frames(args.makeName(clipArg.name + "/anim/frames"),
               clipArg.frameCount(), clipArg.framesPerSecond) {
    glAnimation.name = clipArg.name;

    const auto frameCount = clipArg.frameCount();
    const auto scaleFactor = args.getBakeScaleFactor();

    auto &items = scene.table();

    m_nodeAnimations.reserve(items.size());

    for (auto &pair : items) {
        auto &node = pair.second;
        auto nodeAnimation = node->createAnimation(m_frames, scaleFactor);
        if (nodeAnimation) {
            m_nodeAnimations.emplace_back(std::move(nodeAnimation));
        }
    }

    for (auto relativeFrameIndex = 0; relativeFrameIndex < frameCount;
         ++relativeFrameIndex) {
        const double relativeFrameTime = m_frames.times.at(relativeFrameIndex);
        const MTime absoluteFrameTime =
            clipArg.startTime + MTime(relativeFrameTime, MTime::kSeconds);
        setCurrentTime(absoluteFrameTime, args.redrawViewport);

        NodeTransformCache transformCache;
        for (auto &nodeAnimation : m_nodeAnimations) {
            nodeAnimation->sampleAt(absoluteFrameTime, relativeFrameIndex,
                                    transformCache);
        }

        if (relativeFrameIndex % checkProgressFrameInterval ==
            checkProgressFrameInterval - 1) {
            uiAdvanceProgress(
                "exporting clip '" + clipArg.name +
                formatted("' %d%%", relativeFrameIndex * 100 / frameCount));
        }
    }

    for (auto &nodeAnimation : m_nodeAnimations) {
        nodeAnimation->exportTo(glAnimation);
    }
}

ExportableClip::~ExportableClip() = default;

void ExportableClip::getAllAccessors(
    std::vector<GLTF::Accessor *> &accessors) const {
    m_frames.getAllAccessors(accessors);

    for (auto &&animation : m_nodeAnimations) {
        animation->getAllAccessors(accessors);
    }
}
