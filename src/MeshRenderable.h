#pragma once

#include "sceneTypes.h"
#include "MeshShapesVertexIndexer.h"

class MeshShapesVertexIndexer;

typedef std::vector<std::vector<float>> DrawableComponentsPerSetIndex;
typedef std::array<DrawableComponentsPerSetIndex, Semantic::COUNT> DrawableComponentsPerSetIndexTable;

typedef std::vector<std::vector<float>> ComponentDeltasPerBlendShapeIndex;
typedef std::array<ComponentDeltasPerBlendShapeIndex, Semantic::MORPH_COUNT> ComponentDeltasPerBlendShapeIndexTable;

/**
 * A single renderable part of a mesh, 
 * using just a single index buffer,
 * duplicating components if needed, 
 * reusing as many as possible.
 */
class MeshRenderable
{
public:
	MeshRenderable(
		const int shaderIndex,
		const VertexSignature& signature,
		const MeshShapesVertexIndexer& vertexComponentIndices);

	virtual ~MeshRenderable();

	void dump(const std::string& indent) const;

	const IndexVector& indices() const { return m_indices; }
	const DrawableComponentsPerSetIndexTable& table() const { return m_table; }

	MObject shaderGroup() const { return m_shaderGroup; }

	const int shaderIndex;
	const VertexSignature& vertexSignature;
	const MeshShapesVertexIndexer& vertexComponentIndices;

private:
	IndexVector m_indices;
	MObject m_shaderGroup;
	DrawableComponentsPerSetIndexTable m_table;
	ComponentDeltasPerBlendShapeIndexTable m_deltasTable;

	int m_primaryComponentsCount;
};

