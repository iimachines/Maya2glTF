#pragma once

class MeshBlendShapes;
class MeshShape;
class MeshIndices;

typedef std::vector<const MeshIndices*> MeshIndicesCollection;

struct MeshShapeIndicesOffsets
{
	size_t mainMeshOffset;
	size_t baseShapeOffset;
	size_t blendShapeOffset;
	size_t blendShapeCount;

	MeshShapeIndicesOffsets():mainMeshOffset(-1), baseShapeOffset(-1), blendShapeOffset(-1), blendShapeCount(0)
	{
	}

	bool isBlendShapeOffset(const size_t offset) const
	{
		return offset >= blendShapeOffset && offset < blendShapeOffset + blendShapeCount;
	}
};

/** The indices of the main mesh, the blend shapes (and in the future, the skin weight assignments) */
class MeshShapesIndices 
{
public:
	MeshShapesIndices(const MeshShape& mainShape, const MeshBlendShapes* maybeBlendShapes);
	virtual  ~MeshShapesIndices();

	const MeshShape& mainShape;
	const MeshBlendShapes* maybeBlendShapes;

	const MeshIndicesCollection& collection() const { return m_collection; }

	const MeshShapeIndicesOffsets& offsets() const { return m_offsets; }

	bool hasBlendShapes() const { return maybeBlendShapes != nullptr; }

	/** A vertex will contain the all components of the main shape, all the blend shape deltas, and the skin weight assignments */
	auto maxVertexComponentCount() const { return m_maxVertexComponentCount; }

private:
	MeshIndicesCollection m_collection;
	MeshShapeIndicesOffsets m_offsets;
	size_t m_maxVertexComponentCount;
};
