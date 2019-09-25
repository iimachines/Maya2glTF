#pragma once

#include "BasicTypes.h"

class AccessorPacker {
  public:
    GLTF::Buffer *packAccessors(const std::vector<GLTF::Accessor *> &accessors,
                                const std::string &bufferName);

    std::vector<GLTF::Buffer *> getPackedBuffers() const;

  private:
    std::vector<std::unique_ptr<byte[]>> m_data;
    std::vector<std::unique_ptr<GLTF::Buffer>> m_buffers;
    std::vector<std::unique_ptr<GLTF::BufferView>> m_views;

    GLTF::BufferView *packAccessorsForTargetByteStride(
        const std::vector<GLTF::Accessor *> &accessors,
        GLTF::Constants::WebGL target);
};
