#include "externals.h"

#include "ExportableFrames.h"
#include "accessors.h"

ExportableFrames::ExportableFrames(std::string accessorName,
                                   const int frameCount,
                                   const double framesPerSecond)
    : count(frameCount), m_accessorName(std::move(accessorName)) {
    m_glTimes.reserve(frameCount);

    for (auto relativeFrameIndex = 0; relativeFrameIndex < frameCount; ++relativeFrameIndex) {
        const double relativeFrameTime = relativeFrameIndex / framesPerSecond;
        m_glTimes.emplace_back(static_cast<float>(relativeFrameTime));
    }
}

GLTF::Accessor *ExportableFrames::glInputs() const {
    if (!m_glInputs) {
        m_glInputs = contiguousChannelAccessor(m_accessorName, m_glTimes, 1);
    }

    return m_glInputs.get();
}

GLTF::Accessor *ExportableFrames::glInput0() const {
    if (!m_glInput0) {
        m_glInput0 = contiguousChannelAccessor(m_accessorName, span(m_glTimes).subspan(0, 1), 1);
    }

    return m_glInput0.get();
}

