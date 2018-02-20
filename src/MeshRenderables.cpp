#include "externals.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "MeshShape.h"
#include "MeshShapeCollection.h"
#include "MeshRenderables.h"
#include "IndentableStream.h"
#include "dump.h"

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

	const auto maxVertexElementCount = shapeCollection.maxVertexElementCount();
	const auto maxVertexComponentCount = maxVertexElementCount * 4; // TODO: Compute this
	FloatVector vertexIndexKey;
	VertexLayout vertexLayout;
	vertexLayout.reserve(maxVertexElementCount);
	vertexIndexKey.reserve(maxVertexComponentCount);

	const auto semanticsMask = -1;
	//	= (1 << Semantic::POSITION)
	//	| (1 << Semantic::TEXCOORD)
	//	| (1 << Semantic::NORMAL)
	//	| (1 << Semantic::COLOR)

	//;

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
					if (semanticsMask & (1<<semanticIndex))
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

								const auto& elementIndices = shapeCollection.indicesAt(shapeIndex, semantic, setIndex);
								const auto vertexIndex = elementIndices.at(primitiveVertexIndex);
								const auto& vertexElements = shapeCollection.vertexElementsAt(shapeIndex, semantic, setIndex);
								const auto& source = componentsAt(vertexElements, vertexIndex, semantic);
								vertexIndexKey.insert(vertexIndexKey.end(), source.begin(), source.end());
							}
						}
					}
				}
			}

			// Check if a vertex with exactly the same components already exists. 
			VertexBuffer& vertexBuffer = m_table[vertexSignature];

			auto& componentsMap = vertexBuffer.componentsMap;

			VertexIndex sharedVertexIndex;

			const auto itSharedIndex = vertexBuffer.cache.find(vertexIndexKey);

			if (itSharedIndex == vertexBuffer.cache.end())
			{
				// No vertex with same indices found, create a new output vertex index.
				sharedVertexIndex = static_cast<VertexIndex>(vertexBuffer.cache.size());
				vertexBuffer.cache[vertexIndexKey] = sharedVertexIndex;

				// Build the vertex.
				for (auto&& slot : vertexLayout)
				{
					const auto& elementIndices = shapeCollection.indicesAt(slot.shapeIndex, slot.semantic, slot.setIndex);
					const auto vertexIndex = elementIndices.at(primitiveVertexIndex);
					const auto& vertexElements = shapeCollection.vertexElementsAt(slot.shapeIndex, slot.semantic, slot.setIndex);
					const auto& source = componentsAt(vertexElements, vertexIndex, slot.semantic);
					auto& target = componentsMap[slot];
					if (target.empty())
					{
						target.reserve(vertexCount * slot.dimension());
					}
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
			//VertexLayout& layout = buffer.layout;
			VertexComponentsMap& compMap = buffer.componentsMap;

			auto baseShapeSlots = from(compMap)
				| select([](const auto& pair) { return pair.first; })
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
		}
	}
}

std::ostream& operator<<(std::ostream& out, const VertexSignature& obj)
{
	out << '{' << ' ';
	out << std::quoted("shaderIndex") << ':' << obj.shaderIndex << ',';
	out << std::quoted("slotUsage") << ':' << std::hex << std::setw(8) << obj.slotUsage;
	out << ' ' << '}';
	return out;
}

std::ostream& operator<<(std::ostream& out, const VertexSlot& slot)
{
	out << '{' << ' ';
	out << std::quoted("shapeIndex") << ':' << slot.shapeIndex << ',' << ' ';
	out << std::quoted("setIndex") << ':' << slot.setIndex << ',' << ' ';
	out << std::quoted("semantic") << ':' << std::quoted(Semantic::name(slot.semantic));
	out << ' ' << '}';
	return out;
}

std::ostream& operator<<(std::ostream& out, const VertexBuffer& obj)
{
	out << '{' << endl << indent;

	dump_iterable(out, "indices", obj.indices, obj.indices.size() / obj.cache.size(), 0);

	out << "," << endl;

	dump_iterable(out, "components", obj.componentsMap, 1);

	out << "," << endl;

	out << undent << '}';

	return out;
}
//
//std::ostream& operator<<(std::ostream& out, const MeshRenderables& obj)
//{
//	dump_iterable(out, "renderables", obj.m_table, 1);
//	return out;
//}


