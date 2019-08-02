#pragma once
#include "macros.h"
#include "ShapeIndex.h"

struct WeightPlugEntry
{
    int shapeIndex;
    int plugIndex;
    double originalWeight;
    bool isLocked;
    MPlugArray srcConnections;
    MPlugArray dstConnections;
};

// The weights are sorted by the plug names, to get a stable ordering even when the plugs are re-ordered between scenes.
typedef std::map<std::string, WeightPlugEntry> WeightPlugEntries;

/* 
 * Helper class to sample a blend shape weight plugs 
 * Parts of this code or borrowed from the Maya to OGRE exporter.
 */
class MeshBlendShapeWeights
{
public:
	MeshBlendShapeWeights(const MPlug& weightArrayPlug);
	~MeshBlendShapeWeights();

    const WeightPlugEntries& entries() const { return m_weightPlugEntries; }

	MPlug getWeightPlug(const WeightPlugEntry& entry) const
	{
	    return m_weightArrayPlug[entry.plugIndex];
	}

	void clearWeightsExceptFor(const WeightPlugEntry* fullWeightEntry) const;
	void breakConnections();

    int animatedPlugCount() const;

private:
	DISALLOW_COPY_MOVE_ASSIGN(MeshBlendShapeWeights);

	MPlug m_weightArrayPlug;
	WeightPlugEntries m_weightPlugEntries;
    mutable bool m_isDeformerModified = false;
};

