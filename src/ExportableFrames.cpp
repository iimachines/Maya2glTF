#include "ExportableFrames.h"
#include "accessors.h"
#include "externals.h"

ExportableFrames::ExportableFrames(std::string accessorName,
                                   const int frameCount,
                                   const double framesPerSecond)
    : count(frameCount), m_accessorName(std::move(accessorName)) {
    times.reserve(frameCount);

    for (auto relativeFrameIndex = 0; relativeFrameIndex < frameCount;
         ++relativeFrameIndex) {
        const double relativeFrameTime = relativeFrameIndex / framesPerSecond;
        times.emplace_back(static_cast<float>(relativeFrameTime));
    }
}

GLTF::Accessor *ExportableFrames::glInputs() const {
    if (!m_glInputs) {
        m_glInputs = contiguousChannelAccessor(m_accessorName, times, 1);
    }

    return m_glInputs.get();
}

GLTF::Accessor *ExportableFrames::glInput0() const {
    if (!m_glInput0) {
        m_glInput0 = contiguousChannelAccessor(m_accessorName,
                                               span(times).subspan(0, 1), 1);
    }

    return m_glInput0.get();
}

void ExportableFrames::getAllAccessors(
    std::vector<GLTF::Accessor *> &accessors) const {
    if (m_glInputs) {
        accessors.emplace_back(m_glInputs.get());
    }

    if (m_glInput0) {
        accessors.emplace_back(m_glInput0.get());
    }
}
