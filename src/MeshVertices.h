#pragma once

#include "sceneTypes.h"
#include "MeshSemantics.h"

/** The vertices of a single Maya mesh */
typedef gsl::span<const float> VertexComponents;
typedef std::vector<VertexComponents> VertexComponentsPerSetIndex;
typedef std::array<VertexComponentsPerSetIndex, Semantic::COUNT> VertexComponentsPerSetIndexTable;

class MeshVertices
{
public:
	MeshVertices(const MeshSemantics& names, const MFnMesh& mesh, MSpace::Space space = MSpace::kObject);
	virtual ~MeshVertices();

	const VertexComponentsPerSetIndexTable& table() const { return m_table; }

	void dump(const std::string& name, const std::string& indent) const;
	
	const gsl::span<const float>& vertexComponentsAt(const size_t semanticIndex, const size_t setIndex) const
	{
		return m_table.at(semanticIndex).at(setIndex);
	}

private:
	PositionVector m_positions;
	NormalVector m_normals;
	std::map<SetIndex, TangentVector> m_tangentSets;
	std::map<SetIndex, TexCoordVector> m_uvSets;
	std::map<SetIndex, ColorVector> m_colorSets;

	VertexComponentsPerSetIndexTable m_table;

	DISALLOW_COPY_AND_ASSIGN(MeshVertices);
};
