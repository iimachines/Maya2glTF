#include "MeshBlendShapeWeights.h"
#include "MayaException.h"
#include "externals.h"

void MeshBlendShapeWeights::clearWeightsExceptFor(
    const WeightPlugEntry *fullWeightEntry) const {
    const auto fullWeightIndex =
        fullWeightEntry ? fullWeightEntry->plugIndex : -1;

    for (auto &pair : m_weightPlugEntries) {
        const auto plugIndex = pair.second.plugIndex;

        MStatus status;
        MPlug weightPlug =
            m_weightArrayPlug.elementByLogicalIndex(plugIndex, &status);
        THROW_ON_FAILURE(status);
        weightPlug.setDouble(fullWeightIndex == plugIndex ? 1 : 0);

        m_isDeformerModified = true;
    }
}

MeshBlendShapeWeights::MeshBlendShapeWeights(const MPlug &weightArrayPlug)
    : m_weightArrayPlug(weightArrayPlug) {
    MStatus status;

    // Backup weights and connections.
    const auto numWeights = m_weightArrayPlug.evaluateNumElements(&status);
    THROW_ON_FAILURE(status);

    for (auto weightIndex = 0U; weightIndex < numWeights; ++weightIndex) {
        MPlug weightPlug =
            m_weightArrayPlug.elementByLogicalIndex(weightIndex, &status);
        THROW_ON_FAILURE(status);

        std::string plugName{weightPlug.name(&status).asChar()};
        THROW_ON_FAILURE(status);

        WeightPlugEntry &entry = m_weightPlugEntries[plugName];
        entry.plugIndex = weightIndex;

        entry.originalWeight = weightPlug.asDouble(&status);
        THROW_ON_FAILURE(status);

        entry.isLocked = weightPlug.isLocked(&status);
        THROW_ON_FAILURE(status);

        // Remember connections.
        weightPlug.connectedTo(entry.dstConnections, true, false, &status);
        THROW_ON_FAILURE(status);

        weightPlug.connectedTo(entry.srcConnections, false, true, &status);
        THROW_ON_FAILURE(status);
    }

    // Assign indices based on sorted map order
    int shapeIndex = 0;
    for (auto &&pair : m_weightPlugEntries) {
        pair.second.shapeIndex = shapeIndex++;
    }
}

void MeshBlendShapeWeights::breakConnections() {
    MStatus status;
    MDagModifier dagModifier;

    for (auto &pair : m_weightPlugEntries) {
        const auto weightIndex = pair.second.plugIndex;

        MPlug weightPlug =
            m_weightArrayPlug.elementByLogicalIndex(weightIndex, &status);
        THROW_ON_FAILURE(status);

        THROW_ON_FAILURE(weightPlug.setLocked(false));

        const MPlugArray &dstConnections = pair.second.dstConnections;
        for (auto connectionIndex = 0U;
             connectionIndex < dstConnections.length(); ++connectionIndex) {
            status = dagModifier.disconnect(dstConnections[connectionIndex],
                                            weightPlug);
            THROW_ON_FAILURE(status);
            status = dagModifier.doIt();
            THROW_ON_FAILURE(status);
        }

        m_isDeformerModified = true;
    }
}

int MeshBlendShapeWeights::animatedPlugCount() const {
    int animatedCount = 0;

    for (auto &pair : m_weightPlugEntries) {
        const WeightPlugEntry &entry = pair.second;
        const auto plug = getWeightPlug(entry);

        MStatus status;
        animatedCount += MAnimUtil::isAnimated(plug, false, &status);
    }

    return animatedCount;
}

MeshBlendShapeWeights::~MeshBlendShapeWeights() {
    if (m_isDeformerModified) {
        // We don't throw exceptions in this destructor...
        for (auto &pair : m_weightPlugEntries) {
            const auto *weightName = pair.first.c_str();
            const WeightPlugEntry &entry = pair.second;

            const auto weightIndex = entry.plugIndex;

            MStatus status;

            MPlug weightPlug =
                m_weightArrayPlug.elementByLogicalIndex(weightIndex, &status);
            if (!checkAndReportStatus(
                    status, "Failed to get blend shape weight plug '%s'!",
                    weightName))
                continue;

            if (!checkAndReportStatus(
                    weightPlug.setDouble(entry.originalWeight),
                    "Failed to restore blend shape weight '%s'!", weightName))
                continue;

            if (!checkAndReportStatus(
                    weightPlug.setLocked(entry.isLocked),
                    "Failed to restore blend shape locked state '%s'!",
                    weightName))
                continue;

            MDagModifier dagModifier;
            const MPlugArray &srcConnections = entry.srcConnections;
            const MPlugArray &dstConnections = entry.dstConnections;
            for (auto j = 0U; j < srcConnections.length(); j++) {
                if (!checkAndReportStatus(
                        dagModifier.connect(weightPlug, srcConnections[j]),
                        "Failed to restore blend shape weight source "
                        "connection '%s'!",
                        weightName))
                    continue;

                if (!checkAndReportStatus(dagModifier.doIt(),
                                          "Failed to restore blend shape "
                                          "weight source connection '%s'!",
                                          weightName))
                    continue;
            }

            for (auto j = 0U; j < dstConnections.length(); j++) {
                if (!checkAndReportStatus(
                        dagModifier.connect(dstConnections[j], weightPlug),
                        "Failed to restore blend shape weight destination "
                        "connection '%s'!",
                        weightName))
                    continue;

                if (!checkAndReportStatus(dagModifier.doIt(),
                                          "Failed to restore blend shape "
                                          "weight destination connection '%s'!",
                                          weightName))
                    continue;
            }
        }
    }
}
