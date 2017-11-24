#include "externals.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "MeshShape.h"
#include "MeshShapeCollection.h"
#include "MeshRenderables.h"

using namespace coveo::linq;

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

	const auto primitiveCount = mainIndices.primitiveCount();
	const auto vertexCount = mainIndices.vertexCount();
	const auto perPrimitiveVertexCount = mainIndices.perPrimitiveVertexCount();

	auto shapes = shapeCollection.shapes();

	auto primitiveVertexIndex = 0;

	auto maxVertexElementCount = shapeCollection.maxVertexElementCount();

	IndexVector vertexIndexKey;
	VertexLayout vertexLayout;
	vertexIndexKey.reserve(maxVertexElementCount);
	vertexLayout.reserve(maxVertexElementCount);

	for (auto primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex)
	{
		const auto shaderIndex = shading.primitiveToShaderIndexMap[primitiveIndex];

		for (int counter = perPrimitiveVertexCount; --counter >= 0; ++primitiveVertexIndex)
		{
			// Compute the vertex signature (one bit per semantic+set, 0=unused, 1=used)
			VertexSignature vertexSignature(shaderIndex, 0);

			vertexLayout.clear();
			vertexIndexKey.clear();

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
						const int isUsed = index >= 0;
						vertexSignature.slotUsage <<= 1;
						vertexSignature.slotUsage |= isUsed;
						if (isUsed)
						{
							auto semantic = Semantic::from(semanticIndex);
							vertexLayout.emplace_back(shapeIndex, semantic, setIndex);
							vertexIndexKey.push_back(index);
						}
					}
				}
			}

			VertexBuffer& vertexBuffer = m_table[vertexSignature];

			auto& componentsMap = vertexBuffer.componentsMap;
			if (vertexBuffer.layout.empty())
			{
				vertexBuffer.layout = vertexLayout;
				vertexBuffer.indices.reserve(vertexCount);

				for (auto&& slot : vertexLayout)
				{
					componentsMap[slot].reserve(vertexCount * slot.dimension());
				}
			}
			else
			{
				assert(vertexBuffer.layout == vertexLayout);
			}

			VertexIndex sharedVertexIndex;

			const auto itSharedIndex = vertexBuffer.sharing.find(vertexIndexKey);

			if (itSharedIndex == vertexBuffer.sharing.end())
			{
				// No vertex with same indices found, create a new output vertex index.
				sharedVertexIndex = static_cast<VertexIndex>(vertexBuffer.sharing.size());
				vertexBuffer.sharing[vertexIndexKey] = sharedVertexIndex;

				for (auto&& slot : vertexLayout)
				{
					const auto& elementIndices = shapeCollection.indicesAt(slot.shapeIndex, slot.semantic, slot.setIndex);
					const auto vertexIndex = elementIndices.at(primitiveVertexIndex);
					const auto& vertexElements = shapeCollection.vertexElementsAt(slot.shapeIndex, slot.semantic, slot.setIndex);
					const auto& source = componentsAt(vertexElements, vertexIndex, slot.semantic);
					auto& target = componentsMap.at(slot);
					target.insert(target.end(), source.begin(), source.end());
				}
			}
			else
			{
				// Reuse the same vertex.
				sharedVertexIndex = itSharedIndex->second;
			}

			vertexBuffer.indices.push_back(sharedVertexIndex);
		}
	}

	// Now subtract the blend-shape-base mesh from the blend-shape-targets,
	// and delete the base-mesh
	const auto& meshOffsets = shapeCollection.offsets();
	if (meshOffsets.baseShapeOffset > 0)
	{
		for (auto&& pair : m_table)
		{
			VertexBuffer& buffer = pair.second;
			VertexLayout& layout = buffer.layout;
			VertexComponentsMap& compMap = buffer.componentsMap;

			auto baseShapeSlots = from(layout)
				| where([meshOffsets](const VertexSlot& slot) {return slot.shapeIndex == meshOffsets.baseShapeOffset; })
				| to_vector();

			for (const VertexSlot& baseSlot : baseShapeSlots)
			{
				auto& baseComps = compMap.at(baseSlot);
				auto count = baseComps.size();

				for (int blendShapeIndex: from_int_range(meshOffsets.blendShapeOffset, meshOffsets.blendShapeCount))
				{
					VertexSlot shapeSlot = baseSlot;
					shapeSlot.shapeIndex = blendShapeIndex;
					auto& shapeComps = compMap.at(shapeSlot);

					for (auto index=0; index<count; ++index)
					{
						shapeComps[index] -= baseComps[index];
					}
				}

				// Remove base components.
				compMap.erase(baseSlot);
			}

			// Remove base slots from layout
			std::remove_if(layout.begin(), layout.end(), [meshOffsets](const VertexSlot& slot)
			{
				return slot.shapeIndex == meshOffsets.baseShapeOffset;
			});
		}
	}
}
