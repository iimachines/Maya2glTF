#include "externals.h"
#include "AccessorPacker.h"
#include "accessors.h"

using GLTF::Constants::WebGL;

GLTF::BufferView* AccessorPacker::packAccessorsForTargetByteStride(const std::vector<GLTF::Accessor*>& accessors, WebGL target)
{
    std::map<GLTF::Accessor*, int> byteOffsets;
    int byteLength = 0;
    for (GLTF::Accessor* accessor : accessors)
    {
        const auto componentByteLength = accessor->getComponentByteLength();
        const auto padding = byteLength % componentByteLength;
        if (padding != 0)
        {
            byteLength += (componentByteLength - padding);
        }
        byteOffsets[accessor] = byteLength;
        byteLength += componentByteLength * accessor->getNumberOfComponents() * accessor->count;
    }

    auto bufferData = new byte[byteLength];
    m_data.emplace_back(bufferData);

    const auto bufferView = new GLTF::BufferView(bufferData, byteLength, target);
    m_views.emplace_back(bufferView);

    for (GLTF::Accessor* accessor : accessors)
    {
        const auto byteOffset = byteOffsets[accessor];
        GLTF::Accessor packedAccessor(accessor->type, accessor->componentType, byteOffset, accessor->count, bufferView);

        const size_t numberOfComponents = accessor->getNumberOfComponents();

        const auto components = static_cast<float*>(alloca(sizeof(float) * numberOfComponents));

        for (auto i = 0; i < accessor->count; i++)
        {
            accessor->getComponentAtIndex(i, components);
            packedAccessor.writeComponentAtIndex(i, components);
        }

        accessor->byteOffset = packedAccessor.byteOffset;
        accessor->bufferView = packedAccessor.bufferView;
    }
    return bufferView;
}

void AccessorPacker::packAccessors(const std::vector<GLTF::Accessor*>& accessors, const std::string& bufferName)
{
    std::map<WebGL, std::map<int, std::vector<GLTF::Accessor*>>> accessorGroups;
    accessorGroups[WebGL::ARRAY_BUFFER] = std::map<int, std::vector<GLTF::Accessor*>>();
    accessorGroups[WebGL::ELEMENT_ARRAY_BUFFER] = std::map<int, std::vector<GLTF::Accessor*>>();
    accessorGroups[WebGL(-1)] = std::map<int, std::vector<GLTF::Accessor*>>();

    auto byteLength = 0;
    for (GLTF::Accessor* accessor : accessors)
    {
        // In glTF 2.0, bufferView is not required in accessor.
        if (accessor->bufferView == nullptr)
        {
            continue;
        }

        WebGL target = accessor->bufferView->target;
        auto targetGroup = accessorGroups[target];
        auto byteStride = accessor->getByteStride();
        auto findByteStrideGroup = targetGroup.find(byteStride);

        std::vector<GLTF::Accessor*> byteStrideGroup =
            findByteStrideGroup == targetGroup.end()
            ? std::vector<GLTF::Accessor*>()
            : findByteStrideGroup->second;

        byteStrideGroup.push_back(accessor);
        targetGroup[byteStride] = byteStrideGroup;
        accessorGroups[target] = targetGroup;
        byteLength += accessor->bufferView->byteLength;
    }

#if 0
    // Go through primitives and look for primitives that use Draco extension.
        // If extension is not enabled, the vector will be empty.
    std::vector<GLTF::BufferView*> compressedBufferViews = asset->getAllCompressedBufferView();
    // Reserve data for compressed data.
    for (GLTF::BufferView* compressedBufferView : compressedBufferViews) {
        byteLength += compressedBufferView->byteLength;
    }
#endif

    std::vector<int> byteStrides;
    std::map<int, std::vector<GLTF::BufferView*>> bufferViews;
    for (auto targetGroup : accessorGroups)
    {
        for (auto byteStrideGroup : targetGroup.second)
        {
            const WebGL target = targetGroup.first;
            int byteStride = byteStrideGroup.first;
            
            GLTF::BufferView* bufferView = packAccessorsForTargetByteStride(byteStrideGroup.second, target);

            if (!bufferName.empty())
            {
                bufferView->name = bufferName + "/" + glAccessorTargetPurpose(target) + "-" + std::to_string(byteStride);
            }

            if (target == WebGL::ARRAY_BUFFER)
            {
                bufferView->byteStride = byteStride;
            }
            auto findBufferViews = bufferViews.find(byteStride);
            std::vector<GLTF::BufferView*> bufferViewGroup;
            if (findBufferViews == bufferViews.end())
            {
                byteStrides.push_back(byteStride);
                bufferViewGroup = std::vector<GLTF::BufferView*>();
            }
            else
            {
                bufferViewGroup = findBufferViews->second;
            }
            bufferViewGroup.push_back(bufferView);
            bufferViews[byteStride] = bufferViewGroup;
        }
    }
    std::sort(byteStrides.begin(), byteStrides.end(), std::greater<>());

    if (byteLength > 0)
    {
        // Pack these into a buffer sorted from largest byteStride to smallest
        auto bufferData = new byte[byteLength];
        m_data.emplace_back(bufferData);

        auto buffer = new GLTF::Buffer(bufferData, byteLength);
        m_buffers.emplace_back(buffer);
        buffer->name = bufferName;

        int byteOffset = 0;
        for (int byteStride : byteStrides)
        {
            for (GLTF::BufferView* bufferView : bufferViews[byteStride])
            {
                std::memcpy(&bufferData[byteOffset], bufferView->buffer->data, bufferView->byteLength);
                bufferView->byteOffset = byteOffset;
                bufferView->buffer = buffer;
                byteOffset += bufferView->byteLength;
            }
        }

#if 0
        // Append compressed data to buffer.
        for (GLTF::BufferView* compressedBufferView : compressedBufferViews) {
            std::memcpy(bufferData + byteOffset, compressedBufferView->buffer->data, compressedBufferView->byteLength);
            compressedBufferView->byteOffset = byteOffset;
            compressedBufferView->buffer = buffer;
            byteOffset += compressedBufferView->byteLength;
        }
#endif
    }
}

std::vector<GLTF::Buffer*> AccessorPacker::getPackedBuffers() const
{
    std::vector<GLTF::Buffer*> buffers;
    for (auto && buffer : m_buffers)
    {
        buffers.emplace_back(buffer.get());
    }
    return move(buffers);
}
