#pragma once

#include "MeshIndices.h"
#include "MeshShape.h"
#include "MeshBlendShapes.h"

typedef std::vector<const MeshShape*> MeshShapesVector;

struct MeshShapeOffsets
{
	size_t mainMeshOffset;
	size_t baseShapeOffset;
	size_t blendShapeOffset;
	size_t blendShapeCount;

	MeshShapeOffsets() :mainMeshOffset(-1), baseShapeOffset(-1), blendShapeOffset(-1), blendShapeCount(0)
	{
	}

	bool isBlendShapeOffset(const size_t offset) const
	{
		return offset >= blendShapeOffset && offset < blendShapeOffset + blendShapeCount;
	}
};

/** All the shapes used by a mesh: the main shape, the blend shapes (and in the future, the skin weight assignments) */
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

	/** A vertex will contain the all components of the main shape, all the blend shape deltas, and the skin weight assignments */
	auto maxVertexComponentCount() const { return m_maxVertexComponentCount; }

	auto indexAt(const size_t shapeIndex, const size_t semanticIndex, const size_t setIndex) const
	{
		auto* shape = m_shapes.at(shapeIndex);
		return shape->indices().indexAt(semanticIndex, setIndex);
	}

	const VertexComponents& vertexComponentsAt(const size_t shapeIndex, const size_t semanticIndex, const size_t setIndex) const
	{
		auto* shape = m_shapes.at(shapeIndex);
		return shape->vertices().vertexComponentsAt(semanticIndex, setIndex);
	}

private:
	MeshShapesVector m_shapes;
	MeshShapeOffsets m_offsets;
	size_t m_maxVertexComponentCount;
};
