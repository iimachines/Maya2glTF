#pragma once

#include "Mesh.h"

typedef std::vector<std::vector<float>> DrawableComponentsPerSetIndex;
typedef std::array<DrawableComponentsPerSetIndex, Semantic::COUNT> DrawableComponentsPerSetIndexTable;

/** 
 * Converts a mesh to use just a single index buffer, 
 * copying semantics if needed, reusing as many as possible 
 */
class MeshDrawable
{
public:
	MeshDrawable(const Mesh& mesh);
	virtual ~MeshDrawable();

	void dump(const std::string& name, const std::string& indent) const;

private:
	IndexVector m_indices;
	DrawableComponentsPerSetIndexTable m_table;
};

