#pragma once

#include "sceneTypes.h"

class MeshIndices;
class MeshVertices;
class MeshSemantics;
typedef std::vector<std::vector<float>> DrawableComponentsPerSetIndex;
typedef std::array<DrawableComponentsPerSetIndex, Semantic::COUNT> DrawableComponentsPerSetIndexTable;

/**
 * A single renderable part of a mesh, 
 * using just a single index buffer,
 * duplicating components if needed, 
 * reusing as many as possible.
 */
class MeshRenderable
{
public:
	MeshRenderable(const int shaderIndex,
		const MeshSemantics& meshSemantics,
		const MeshVertices& meshVertices,
		const MeshIndices& meshIndices);

	virtual ~MeshRenderable();

	void dump(const std::string& indent) const;

	const int shaderIndex;
	const MFnDependencyNode shaderNode;
	const std::string shaderName;

	const IndexVector& indices() const { return m_indices; }
	const DrawableComponentsPerSetIndexTable& table() const { return m_table; }

private:
	IndexVector m_indices;
	DrawableComponentsPerSetIndexTable m_table;
};

