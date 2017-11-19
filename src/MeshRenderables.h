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
	VertexSlot()
		: shapeIndex(-1)
		, semantic(Semantic::Kind::INVALID)
		, setIndex(-1)
	{
	}

	VertexSlot(const ShapeIndex shapeIndex, const Semantic::Kind semantic, const SetIndex setIndex)
		: shapeIndex(shapeIndex)
		, semantic(semantic)
		, setIndex(setIndex)
	{
	}

	VertexSlot(const VertexSlot& slot)
		: shapeIndex(slot.shapeIndex)
		, semantic(slot.semantic)
		, setIndex(slot.setIndex)
	{
	}

	ShapeIndex shapeIndex;
	Semantic::Kind semantic;
	SetIndex setIndex;

	friend bool operator==(const VertexSlot& x, const VertexSlot& y)
	{
		return x.shapeIndex == y.shapeIndex &&
			x.semantic == y.semantic &&
			x.setIndex == y.setIndex;
	}

	size_t dimension() const
	{
		return Semantic::dimension(semantic);
	}
};



typedef std::vector<VertexSlot> VertexLayout;

static size_t dimension_of(const VertexLayout& layout)
{
	size_t sum = 0;
	for (auto && slot : layout)
	{
		sum += slot.dimension();
	}
	return sum;
}

// TODO: Use unordered_map here
typedef std::map<IndexVector, Index> VertexSharingMap;

struct VertexBuffer
{
	VertexSharingMap sharing;
	VertexLayout layout;
	IndexVector indices;
	FloatVector components;
};

typedef std::unordered_map<VertexSignature, VertexBuffer> VertexBufferMap;
typedef std::unordered_map<ShaderIndex, VertexBufferMap> VertexBuffersTable;

class MeshShapeCollection;

class MeshRenderables
{
public:
	MeshRenderables(
		const InstanceIndex instanceIndex,
		const MeshShapeCollection& shapes);

	const InstanceIndex instanceIndex;
	const MeshShapeCollection& meshShapesIndices;

	const VertexBuffersTable& table() const { return m_table; }

	//void dump(const std::string& name, const std::string& indent) const;

private:
	VertexBuffersTable m_table;
};
