#include "externals.h"
#include "MeshShapeCollection.h"
#include "MeshShape.h"
#include "MeshBlendShapes.h"
#include "dump.h"

MeshShapeCollection::MeshShapeCollection(const MeshShape& mainShape, const MeshBlendShapes* maybeBlendShapes)
	: mainShape(mainShape)
	, maybeBlendShapes(maybeBlendShapes)
	, m_maxVertexComponentCount(0)
{
	m_shapes.push_back(&mainShape);

	m_offsets.mainMeshOffset = 0;

	const auto vertexCount = mainShape.indices().vertexCount();

	const auto hasBlendShapes = maybeBlendShapes && !maybeBlendShapes->empty();

	// Verify that all blend-shapes have the same "topology"
	if (hasBlendShapes)
	{
		m_offsets.baseShapeOffset = 1;
		m_offsets.blendShapeOffset = 2;

		const auto* baseShape = maybeBlendShapes->baseShape();

		if (baseShape->indices().vertexCount() != vertexCount)
			throw std::runtime_error(formatted("Base shape '%s' has different topology from '%s'!",
				mainShape.dagPath().fullPathName().asChar(), baseShape->dagPath().fullPathName().asChar()));

		m_shapes.push_back(baseShape);

		m_offsets.blendShapeCount = maybeBlendShapes->entries().size();

		for (auto&& entry : maybeBlendShapes->entries())
		{
			const auto& shape = entry->shape;
			if (shape.indices().vertexCount() != vertexCount)
				throw std::runtime_error(formatted("Blend shape '%s' has different topology from '%s'!",
					mainShape.dagPath().fullPathName().asChar(), shape.dagPath().fullPathName().asChar()));

			m_shapes.push_back(&shape);
		}
	}

	size_t maxVertexComponentCount = 0;

	for (auto* shape : m_shapes)
	{
		for (auto && indicesPerSet : shape->indices().table())
		{
			maxVertexComponentCount += indicesPerSet.size();
		}
	}

	m_maxVertexComponentCount = maxVertexComponentCount;
}

MeshShapeCollection::~MeshShapeCollection()
{
}
