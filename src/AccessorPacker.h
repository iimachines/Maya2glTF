#pragma once

#include "BasicTypes.h"

class AccessorPacker
{
public:
    void packAccessors(const std::vector<GLTF::Accessor*>& accessors);

    std::vector<GLTF::Buffer*> getPackedBuffers() const;

private:
    std::vector<std::unique_ptr<byte[]>> m_data;
    std::vector<std::unique_ptr<GLTF::Buffer>> m_buffers;
    std::vector<std::unique_ptr<GLTF::BufferView>> m_views;
    std::vector<std::unique_ptr<GLTF::Accessor>> m_accessors;

    GLTF::BufferView* packAccessorsForTargetByteStride(const std::vector<GLTF::Accessor*>& accessors, GLTF::Constants::WebGL target);
};
