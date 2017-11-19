#include "externals.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "MeshShape.h"
#include "MeshShapeCollection.h"
#include "MeshRenderables.h"

MeshRenderables::MeshRenderables(
	const InstanceIndex instanceIndex,
	const MeshShapeCollection& shapeCollection)
	: instanceIndex(instanceIndex)
	, meshShapesIndices(shapeCollection)
{
	MStatus status;

	const auto& mainIndices = shapeCollection.mainShape.indices();

	auto& shadingPerInstance = mainIndices.shadingPerInstance();

	auto& shading = shadingPerInstance.at(instanceIndex);
	const auto shaderCount = shading.shaderCount();

	const auto primitiveCount = mainIndices.primitiveCount();
	const auto vertexCount = mainIndices.vertexCount();
	const auto perPrimitiveVertexCount = mainIndices.perPrimitiveVertexCount();

	auto shapes = shapeCollection.shapes();

	auto primitiveVertexIndex = 0;

	auto maxVertexComponentCount = shapeCollection.maxVertexComponentCount();

	IndexVector vertexIndexKey;
	VertexLayout vertexLayout;
	vertexIndexKey.resize(maxVertexComponentCount);
	vertexLayout.resize(maxVertexComponentCount);

	for (auto primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex)
	{
		const auto shaderIndex = shading.primitiveToShaderIndexMap[primitiveIndex];

		VertexBufferMap& vertexBufferMap = m_table[shaderIndex];

		// Determine signature (used semantics per shader)
		for (int counter = perPrimitiveVertexCount; --counter >= 0; ++primitiveVertexIndex)
		{
			// Compute the vertex signature (a bit per used semantic+set)
			VertexSignature vertexSignature = 0;

			size_t signatureBit = 0;

			for (auto shapeIndex = 0; shapeIndex < shapes.size(); ++shapeIndex)
			{
				const auto& shapeIndicesTable = shapes.at(shapeIndex)->indices().table();
				for (auto semanticIndex = 0; semanticIndex < shapeIndicesTable.size(); ++semanticIndex)
				{
					const auto & indicesPerSet = shapeIndicesTable[semanticIndex];

					for (auto setIndex = 0; setIndex < indicesPerSet.size(); ++setIndex)
					{
						const auto& indices = indicesPerSet.at(setIndex);
						const auto index = indices[primitiveVertexIndex];
						const bool isUsed = index >= 0;
						vertexSignature.set(signatureBit++, isUsed);
						if (isUsed)
						{
							vertexLayout.emplace_back(shapeIndex, Semantic::from(semanticIndex), setIndex);
							vertexIndexKey.push_back(index);
						}
					}
				}
			}

			VertexBuffer& vertexBuffer = vertexBufferMap[vertexSignature];

			if (vertexBuffer.layout.empty())
			{
				vertexBuffer.layout = vertexLayout;
				vertexBuffer.indices.reserve(vertexCount);

				auto dimension = dimension_of(vertexLayout);
				vertexBuffer.components.reserve(dimension* vertexCount);
			}
			else
			{
				assert(vertexBuffer.layout == vertexLayout);
			}

			VertexIndex sharedVertexIndex;

			const auto itSharedIndex = vertexBuffer.sharing.find(vertexIndexKey);

			if (itSharedIndex == vertexBuffer.sharing.end())
			{
				// No vertex with same indices found, add a new one.
				sharedVertexIndex = static_cast<VertexIndex>(vertexBuffer.sharing.size());
				vertexBuffer.sharing[vertexIndexKey] = sharedVertexIndex;

				for (auto&& slot : vertexLayout)
				{
					auto index = shapeCollection.indexAt(slot.shapeIndex, slot.semantic, slot.setIndex);
					auto& components = shapeCollection.vertexComponentsAt(slot.shapeIndex, slot.semantic, slot.setIndex);
					vertexBuffer.components.insert(vertexBuffer.components.end(), components.begin(), components.end());
				}
			}
			else
			{
				sharedVertexIndex = itSharedIndex->second;
			}

			vertexBuffer.indices.push_back(sharedVertexIndex);
		}
	}
}
