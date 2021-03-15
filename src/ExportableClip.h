#pragma once

#include "Arguments.h"
#include "ExportableFrames.h"
#include "NodeAnimation.h"

class ExportableClip {
  public:
    ExportableClip(const Arguments &args, const AnimClipArg &clipArg, const ExportableScene &scene);
    virtual ~ExportableClip();

    GLTF::Animation glAnimation;

  private:
    ExportableFrames m_frames;
    std::vector<std::unique_ptr<NodeAnimation>> m_nodeAnimations;

    DISALLOW_COPY_MOVE_ASSIGN(ExportableClip);
};
