#include "externals.h"
#include "MeshShapesIndices.h"
#include "MeshShape.h"
#include "MeshBlendShapes.h"
#include "dump.h"

MeshShapesIndices::MeshShapesIndices(const MeshShape& mainShape, const MeshBlendShapes* maybeBlendShapes)
	: mainShape(mainShape)
	, maybeBlendShapes(maybeBlendShapes)
	, m_maxVertexComponentCount(0)
{
	const auto& meshIndices = mainShape.indices();
	m_collection.push_back(&meshIndices);

	m_offsets.mainMeshOffset = 0;

	const auto vertexCount = meshIndices.vertexCount();

	const auto hasBlendShapes = maybeBlendShapes && !maybeBlendShapes->empty();

	// Verify that all blend-shapes have the same "topology"
	if (hasBlendShapes)
	{
		m_offsets.baseShapeOffset = 1;
		m_offsets.blendShapeOffset = 2;

		const auto baseShape = maybeBlendShapes->baseShape();

		if (baseShape->indices().vertexCount() != vertexCount)
			throw std::runtime_error(formatted("Base shape '%s' has different topology from '%s'!",
				mainShape.dagPath().fullPathName().asChar(), baseShape->dagPath().fullPathName().asChar()));

		m_collection.push_back(&baseShape->indices());

		m_offsets.blendShapeCount = maybeBlendShapes->entries().size();

		for (auto&& entry : maybeBlendShapes->entries())
		{
			const auto& shape = entry->shape;
			if (shape.indices().vertexCount() != vertexCount)
				throw std::runtime_error(formatted("Blend shape '%s' has different topology from '%s'!",
					mainShape.dagPath().fullPathName().asChar(), shape.dagPath().fullPathName().asChar()));

			m_collection.push_back(&meshIndices);
		}
	}

	auto maxVertexComponentCount = 0;

	for (auto* shapeIndices : m_collection)
	{
		for (auto && indicesPerSet : shapeIndices->table())
		{
			maxVertexComponentCount += indicesPerSet.size();
		}
	}

	m_maxVertexComponentCount = maxVertexComponentCount;
}

MeshShapesIndices::~MeshShapesIndices()
{
}
