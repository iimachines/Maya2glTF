#pragma once

#include "sceneTypes.h"

class MeshShape;
class MeshBlendShapes;

/** 
 * For each semantic/set-index pair, per shader, for both main mesh and blend-shapes, 
 * a bit to indicate if a vertex component has this semantic/set-index 
 * For example, some of the vertices of a Maya mesh might not have UVs, colors, etc...
 * TODO: Simpify this! 
 */

typedef int PrimitiveVertexIndex;
typedef std::vector<bool> MeshVertexSignature;
typedef std::unordered_map<PrimitiveVertexIndex, IndexVector> MeshVertexComponentIndices;
typedef std::unordered_map<MeshVertexSignature, MeshVertexComponentIndices> MeshVertexComponentIndicesTable;

// The indices of the main mesh, the blend shapes (and in the future, the skin weight assignments)
typedef std::vector<MeshIndices*> MeshIndicesCollection;

class MeshVertexComponentMappings
{
public:
	MeshVertexComponentMappings(
		const InstanceIndex instanceIndex,
		const MeshIndicesCollection& meshIndicesCollection);

	const InstanceIndex instanceIndex;

	const MeshVertexComponentIndicesTable& table() const { return m_table; }

private:
	MeshVertexComponentIndicesTable m_table;
};
