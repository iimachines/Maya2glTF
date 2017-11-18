#pragma once

#include "sceneTypes.h"

class MeshShape;
class MeshBlendShapes;

typedef std::vector<std::vector<float>> DrawableComponentsPerSetIndex;
typedef std::array<DrawableComponentsPerSetIndex, Semantic::COUNT> DrawableComponentsPerSetIndexTable;

typedef std::map<int, std::vector<float>> ComponentDeltasPerBlendShapeIndex;
typedef std::array<ComponentDeltasPerBlendShapeIndex, Semantic::COUNT> ComponentDeltasPerBlendShapeIndexTable;

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
		const int meshInstanceIndex,
		const int meshShaderIndex,
		const MeshShape& meshShape,
		const MeshBlendShapes* maybeBlendShapes);

	virtual ~MeshRenderable();

	void dump(const std::string& indent) const;

	const IndexVector& indices() const { return m_indices; }
	const DrawableComponentsPerSetIndexTable& table() const { return m_table; }

	MObject shaderGroup() const { return m_shaderGroup; }

	const int meshInstanceIndex;
	const int meshShaderIndex;

private:
	IndexVector m_indices;
	MObject m_shaderGroup;
	DrawableComponentsPerSetIndexTable m_table;
	ComponentDeltasPerBlendShapeIndexTable m_deltasTable;

	int m_primaryComponentsCount;
};

