#include "externals.h"
#include "MeshBlendShapeWeights.h"
#include "MayaException.h"

void MeshBlendShapeWeights::clearWeightsExceptFor(const size_t index) const
{
	const auto numWeights = m_originalWeightPlugStates.size();

	for (auto weightIndex = 0U; weightIndex<numWeights; ++weightIndex)
	{
		MStatus status;
		MPlug weightPlug = m_weightArrayPlug.elementByLogicalIndex(weightIndex, &status);
		THROW_ON_FAILURE(status);
		weightPlug.setDouble(weightIndex == index ? 1 : 0);
	}
}

MeshBlendShapeWeights::MeshBlendShapeWeights(const MPlug& weightArrayPlug)
:m_weightArrayPlug(weightArrayPlug)
{
	MStatus status;

	// Backup weights and connections.
	const auto numWeights = m_weightArrayPlug.evaluateNumElements(&status);
	THROW_ON_FAILURE(status);

	m_originalWeightPlugStates.reserve(numWeights);

	for (auto weightIndex = 0U; weightIndex<numWeights; ++weightIndex)
	{
		OriginalWeightPlugState state;

		MPlug weightPlug = m_weightArrayPlug.elementByLogicalIndex(weightIndex, &status);
		THROW_ON_FAILURE(status);
		state.weight = weightPlug.asDouble();

		state.locked = weightPlug.isLocked(&status);
		THROW_ON_FAILURE(status);

		// Remember connections.
		weightPlug.connectedTo(state.dstConnections, true, false, &status);
		THROW_ON_FAILURE(status);
		weightPlug.connectedTo(state.srcConnections, false, true, &status);
		THROW_ON_FAILURE(status);

		m_originalWeightPlugStates.push_back(state);
	}
}

void MeshBlendShapeWeights::breakConnections()
{
	MStatus status;
	MDagModifier dagModifier;

	const auto numWeights = m_originalWeightPlugStates.size();
	for (auto weightIndex = 0U; weightIndex<numWeights; ++weightIndex)
	{
		MPlug weightPlug = m_weightArrayPlug.elementByLogicalIndex(weightIndex, &status);
		THROW_ON_FAILURE(status);

		THROW_ON_FAILURE(weightPlug.setLocked(false));

		const MPlugArray& dstConnections = m_originalWeightPlugStates[weightIndex].dstConnections;
		for (auto connectionIndex = 0U; connectionIndex<dstConnections.length(); ++connectionIndex)
		{
			status = dagModifier.disconnect(dstConnections[connectionIndex], weightPlug);
			THROW_ON_FAILURE(status);
			status = dagModifier.doIt();
			THROW_ON_FAILURE(status);
		}
	}
}

MeshBlendShapeWeights::~MeshBlendShapeWeights()
{
	// We don't throw exceptions in this destructor...
	const auto numWeights = m_originalWeightPlugStates.size();

	for (auto weightIndex = 0U; weightIndex<numWeights; ++weightIndex)
	{
		MStatus status;

		const OriginalWeightPlugState& state = m_originalWeightPlugStates[weightIndex];

		MPlug weightPlug = m_weightArrayPlug.elementByLogicalIndex(weightIndex, &status);
		if (!checkAndReportStatus(status,
			"Failed to get blend shape weight plug #%d!", weightIndex))
			continue;

		if (!checkAndReportStatus(weightPlug.setDouble(state.weight),
			"Failed to restore blend shape weight #%d!", weightIndex))
			continue;

		if (!checkAndReportStatus(weightPlug.setLocked(state.locked),
			"Failed to restore blend shape locked state #%d!", weightIndex))
			continue;

		MDagModifier dagModifier;
		const MPlugArray& srcConnections = state.srcConnections;
		const MPlugArray& dstConnections = state.dstConnections;
		for (auto j = 0U; j<srcConnections.length(); j++)
		{
			if (!checkAndReportStatus(dagModifier.connect(weightPlug, srcConnections[j]),
				"Failed to restore blend shape weight source connection #%d!", weightIndex))
				continue;

			if (!checkAndReportStatus(dagModifier.doIt(),
				"Failed to restore blend shape weight source connection #%d!", weightIndex))
				continue;
		}

		for (auto j = 0U; j<dstConnections.length(); j++)
		{
			if (!checkAndReportStatus(dagModifier.connect(dstConnections[j], weightPlug),
				"Failed to restore blend shape weight destination connection #%d!", weightIndex))
				continue;

			if (!checkAndReportStatus(dagModifier.doIt(),
				"Failed to restore blend shape weight destination connection #%d!", weightIndex))
				continue;
		}
	}
}
