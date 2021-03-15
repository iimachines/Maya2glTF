#pragma once

#include "macros.h"

class ExportableFrames {
  public:
    ExportableFrames(std::string accessorName, int frameCount, double framesPerSecond);
    ~ExportableFrames() = default;

    const int count;

    GLTF::Accessor *glInputs() const;

    GLTF::Accessor *glInput0() const;

  private:
    const std::string m_accessorName;

    // For each animation frame, the clip-relative time in seconds.
    std::vector<float> m_glTimes;

    mutable std::unique_ptr<GLTF::Accessor> m_glInputs;
    mutable std::unique_ptr<GLTF::Accessor> m_glInput0;

    DISALLOW_COPY_MOVE_ASSIGN(ExportableFrames);
};
