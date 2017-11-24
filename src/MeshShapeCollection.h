#pragma once

#include "MeshIndices.h"
#include "MeshShape.h"
#include "MeshBlendShapes.h"

typedef std::vector<const MeshShape*> MeshShapesVector;

struct MeshShapeOffsets
{
	int mainMeshOffset;
	int baseShapeOffset;
	int blendShapeOffset;
	int blendShapeCount;

	MeshShapeOffsets() :mainMeshOffset(-1), baseShapeOffset(-1), blendShapeOffset(-1), blendShapeCount(0)
	{
	}

	bool isBlendShapeOffset(const size_t offset) const
	{
		return offset >= blendShapeOffset && offset < blendShapeOffset + blendShapeCount;
	}
};

/** 
 * All the shapes used by a mesh: the main shape or the blend shapes (including the base shape) 
 * (and in the future, the skin weight assignments) 
 */
class MeshShapeCollection
{
public:
	MeshShapeCollection(const MeshShape& mainShape, const MeshBlendShapes* maybeBlendShapes);
	virtual  ~MeshShapeCollection();

	const MeshShape& mainShape;
	const MeshBlendShapes* maybeBlendShapes;

	const MeshShapesVector& shapes() const { return m_shapes; }

	const MeshShapeOffsets& offsets() const { return m_offsets; }

	bool hasBlendShapes() const { return maybeBlendShapes != nullptr; }

	/** A vertex will contain the all elements of the main shape, all the blend shape deltas, and the skin weight assignments */
	auto maxVertexElementCount() const { return m_maxVertexElementCount; }

	const IndexVector& indicesAt(const size_t shapeIndex, const size_t semanticIndex, const size_t setIndex) const
	{
		auto* shape = m_shapes.at(shapeIndex);
		return shape->indices().indicesAt(semanticIndex, setIndex);
	}

	const VertexComponents& vertexElementsAt(const size_t shapeIndex, const size_t semanticIndex, const size_t setIndex) const
	{
		auto* shape = m_shapes.at(shapeIndex);
		return shape->vertices().vertexElementComponentsAt(semanticIndex, setIndex);
	}

private:
	MeshShapesVector m_shapes;
	MeshShapeOffsets m_offsets;
	size_t m_maxVertexElementCount;
};
