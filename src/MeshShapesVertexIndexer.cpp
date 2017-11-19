#include "externals.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "MeshShape.h"
#include "MeshShapesIndices.h"
#include "MeshShapesVertexIndexer.h"

MeshShapesVertexIndexer::MeshShapesVertexIndexer(
	const InstanceIndex instanceIndex,
	const MeshShapesIndices& meshShapesIndices)
	: instanceIndex(instanceIndex)
	, meshShapesIndices(meshShapesIndices)
{
	MStatus status;

	const auto& meshIndices = meshShapesIndices.mainShape.indices();

	auto& shadingPerInstance = meshIndices.shadingPerInstance();

	auto& shading = shadingPerInstance.at(instanceIndex);
	const auto shaderCount = shading.shaderCount();

	const auto primitiveCount = meshIndices.primitiveCount();
	const auto vertexCount = meshIndices.vertexCount();
	const auto perPrimitiveVertexCount = meshIndices.perPrimitiveVertexCount();

	auto shapesIndices = meshShapesIndices.collection();

	auto primitiveVertexIndex = 0;

	auto maxVertexComponentCount = meshShapesIndices.maxVertexComponentCount();

	VertexLayout vertexLayout;
	vertexLayout.reserve(maxVertexComponentCount);

	// Preallocate the index buffer (otherwise we end up with a new allocation per vertex)
	m_indexBuffer.resize(vertexCount * maxVertexComponentCount);
	m_vertexSignatures.resize(vertexCount);

	auto indexBufferOffset = 0;

	for (auto primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex)
	{
		// If the primitive is not shaded in Maya, we skip it.
		// TODO: Maybe we should export these too?
		auto shaderIndex = shading.primitiveToShaderIndexMap[primitiveIndex];
		if (shaderIndex < 0)
			continue;

		// Determine signature (used semantics per shader)
		for (int counter = perPrimitiveVertexCount; --counter >= 0; ++primitiveVertexIndex)
		{
			VertexSignature vertexSignature = 0;
			vertexLayout.clear();

			const auto indexBufferStart = indexBufferOffset;

			// Allocate component vectors
			auto signatureBit = 0;

			for (auto shapeIndex = 0; shapeIndex < shapesIndices.size(); ++shapeIndex)
			{
				const auto& shapeIndicesTable = shapesIndices.at(shapeIndex)->table();
				for (auto semanticIndex = 0; semanticIndex<shapeIndicesTable.size(); ++semanticIndex)
				{
					const auto & indicesPerSet = shapeIndicesTable[semanticIndex];

					for (auto setIndex = 0; setIndex < indicesPerSet.size(); ++setIndex)
					{
						const auto&  indices = indicesPerSet.at(setIndex);
						const auto index = indices[primitiveVertexIndex];
						const bool isUsed = index >= 0;
						vertexSignature.set(signatureBit++, isUsed);
						if (isUsed)
						{
							vertexLayout.emplace_back(shapeIndex, Semantic::from(semanticIndex), setIndex);
							m_indexBuffer[indexBufferOffset++] = index;
						}
					}
				}
			}

			m_vertexSignatures.push_back(vertexSignature);

			auto layoutIt = m_vertexLayoutMap.find(vertexSignature);
			if (layoutIt == m_vertexLayoutMap.end())
			{
				m_vertexLayoutMap[vertexSignature] = vertexLayout;
			}
			else
			{
				assert(layoutIt->second == vertexLayout);
			}

			const auto vertexComponentSize = indexBufferOffset - indexBufferStart;

			if (vertexComponentSize > 0)
			{
				auto span = gsl::make_span(&m_indexBuffer[indexBufferOffset], vertexComponentSize);
				m_vertexComponentIndices.emplace_back(span);
			}
			else
			{
				// This vertex has no indices (it is not shaded)
				m_vertexComponentIndices.emplace_back();
			}
		}
	}
}
