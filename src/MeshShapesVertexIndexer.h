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

typedef int VertexIndex;

// TODO: We currently do not support more than 128 components per vertex!
const int MAX_COMPONENTS_PER_VERTEX = 128;

typedef std::bitset<MAX_COMPONENTS_PER_VERTEX> VertexSignature;

typedef int ShapeIndex;

struct VertexSlot
{
	VertexSlot(const ShapeIndex shapeIndex, const Semantic::Kind semantic, const SetIndex setIndex)
		: shapeIndex(shapeIndex),
		  semantic(semantic),
		  setIndex(setIndex)
	{
	}

	const ShapeIndex shapeIndex;
	const Semantic::Kind semantic;
	const SetIndex setIndex;
};

typedef std::vector<VertexSlot> VertexLayout;
typedef std::vector<VertexSignature> VertexSignatures;
typedef std::map<VertexSignature, VertexLayout> VertexLayoutMap;
typedef std::vector<IndexSpan> VertexComponentIndices;

class MeshShapesIndices;

class MeshShapesVertexIndexer
{
public:
	MeshShapesVertexIndexer(
		const InstanceIndex instanceIndex,
		const MeshShapesIndices& meshShapesIndices);

	const InstanceIndex instanceIndex;
	const MeshShapesIndices& meshShapesIndices;

	const VertexLayoutMap& vertexLayoutMap() const { return m_vertexLayoutMap; }
	const VertexSignatures& vertexSignatures() const { return m_vertexSignatures; }
	const VertexComponentIndices& vertexComponentIndices() const { return m_vertexComponentIndices; }

	void dump(const std::string& name, const std::string& indent) const;

private:
	VertexLayoutMap m_vertexLayoutMap;
	VertexSignatures m_vertexSignatures;
	VertexComponentIndices m_vertexComponentIndices;
	IndexVector m_indexBuffer;
};
