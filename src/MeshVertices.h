#pragma once

#include "sceneTypes.h"
#include "Spans.h"
#include "MeshSemantics.h"

/** The vertices of a single Maya mesh */
typedef std::vector<gsl::span<const float>> MeshComponentsPerSetIndex;
typedef std::array<MeshComponentsPerSetIndex, Semantic::COUNT> MeshComponentsPerSetIndexTable;

class MeshVertices
{
public:
	MeshVertices(const MeshSemantics& names, const MFnMesh& mesh, MSpace::Space space = MSpace::kObject);
	virtual ~MeshVertices();

	const MeshComponentsPerSetIndexTable& table() const { return m_table; }

	void dump(const std::string& name, const std::string& indent) const;

private:
	MFloatPointArray m_positions;
	MFloatVectorArray m_normals;
	std::map<SetIndex, Float2Vector> m_uvSets;
	std::map<SetIndex, MColorArray> m_colorSets;

	MeshComponentsPerSetIndexTable m_table;

	DISALLOW_COPY_AND_ASSIGN(MeshVertices);
};
