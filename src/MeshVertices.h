#pragma once

#include "sceneTypes.h"
#include "MeshSemantics.h"

/** The vertices of a single Maya mesh (components stored sequentially, ie [x0, y0, z0, x1, y1, z1, ...])  */
typedef gsl::span<const float> VertexComponents;
typedef std::vector<VertexComponents> VertexElementsPerSetIndex;
typedef std::array<VertexElementsPerSetIndex, Semantic::COUNT> VertexElementsPerSetIndexTable;

inline VertexComponents componentsAt(const VertexComponents& elements, const size_t vertexIndex, const Semantic::Kind semantic)
{
	const auto count = Semantic::dimension(semantic);
	return elements.subspan(vertexIndex*count, count);
}

class MeshVertices
{
public:
	MeshVertices(const MeshSemantics& names, const MFnMesh& mesh, MSpace::Space space = MSpace::kTransform);
	virtual ~MeshVertices();

	const VertexElementsPerSetIndexTable& table() const { return m_table; }

	void dump(const std::string& name, const std::string& indent) const;
	
	const VertexComponents& vertexElementComponentsAt(const size_t semanticIndex, const size_t setIndex) const
	{
		return m_table.at(semanticIndex).at(setIndex);
	}

private:
	PositionVector m_positions;
	NormalVector m_normals;
	std::map<SetIndex, TangentVector> m_tangentSets;
	std::map<SetIndex, TexCoordVector> m_uvSets;
	std::map<SetIndex, ColorVector> m_colorSets;

	VertexElementsPerSetIndexTable m_table;

	DISALLOW_COPY_AND_ASSIGN(MeshVertices);
};
