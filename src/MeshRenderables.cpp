#include "externals.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "Mesh.h"
#include "MeshRenderables.h"
#include "IndentableStream.h"
#include "dump.h"
#include "MayaException.h"
#include "Arguments.h"

using namespace coveo::linq;

MeshRenderables::MeshRenderables(
	const InstanceIndex instanceIndex,
	const MeshShapes& meshShapes,
	const Arguments& args)
	: instanceIndex(instanceIndex)
{
	CONSTRUCTOR_BEGIN();

	MStatus status;

	const auto& mainIndices = meshShapes.at(0)->indices();

	auto& shadingPerInstance = mainIndices.shadingPerInstance();

	auto& shading = shadingPerInstance.at(instanceIndex);

	const auto primitiveCount = mainIndices.primitiveCount();
	const auto vertexCount = mainIndices.maxVertexCount();
	const auto perPrimitiveVertexCount = mainIndices.perPrimitiveVertexCount();

	auto primitiveVertexIndex = 0;

	size_t maxVertexElementCount = 0;
	size_t maxVertexComponentCount = 0;

	for (auto& shape : meshShapes)
	{
		auto& indicesTable = shape->indices().table();

		for (auto semanticIndex=0U; semanticIndex<indicesTable.size(); ++semanticIndex)
		{
			const auto elementCount = indicesTable.at(semanticIndex).size();
			maxVertexElementCount += elementCount;
			maxVertexComponentCount += elementCount * dimension(Semantic::from(semanticIndex), shape->shapeIndex);
		}
	}

	FloatVector vertexIndexKey;
	VertexLayout vertexLayout;
	vertexLayout.reserve(maxVertexElementCount);
	vertexIndexKey.reserve(maxVertexComponentCount);

	const auto semanticsMask = args.meshPrimitiveAttributes;

	for (auto primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex)
	{
		const auto shaderIndex = shading.primitiveToShaderIndexMap[primitiveIndex];

		for (int counter = perPrimitiveVertexCount; --counter >= 0; ++primitiveVertexIndex)
		{
			// Compute the vertex signature (one bit per semantic+set, 0=unused, 1=used)
			VertexSignature vertexSignature(shaderIndex, 0);

			vertexLayout.clear();
			vertexIndexKey.clear();

			for (auto shapeIndex = 0U; shapeIndex < meshShapes.size(); ++shapeIndex)
			{
				auto& shape = meshShapes.at(shapeIndex);
				const auto& shapeIndicesTable = shape->indices().table();
				const auto& shapeVerticesTable = shape->vertices().table();

				for (auto semanticIndex = 0U; semanticIndex < shapeIndicesTable.size(); ++semanticIndex)
				{
					if (semanticsMask.test(semanticIndex))
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
								vertexLayout.emplace_back(ShapeIndex::shape(shapeIndex), semantic, setIndex);

								const auto& elementIndices = shapeIndicesTable.at(semantic).at(setIndex);
								const auto vertexIndex = elementIndices.at(primitiveVertexIndex);
								const auto& vertexElements = shapeVerticesTable.at(semantic).at(setIndex);
								const auto& source = componentsAt(vertexElements, vertexIndex, semantic, shape->shapeIndex);
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

			const auto itSharedIndex = vertexBuffer.vertexToIndexMapping.find(vertexIndexKey);

			if (itSharedIndex == vertexBuffer.vertexToIndexMapping.end())
			{
				// No vertex with same indices found, create a new output vertex index.
				sharedVertexIndex = static_cast<VertexIndex>(vertexBuffer.vertexToIndexMapping.size());
				vertexBuffer.vertexToIndexMapping[vertexIndexKey] = sharedVertexIndex;

				// Build the vertex.
				for (auto&& slot : vertexLayout)
				{
					auto& shape = meshShapes.at(slot.shapeIndex.arrayIndex());

					const auto& elementIndices = shape->indices().indicesAt(slot.semantic, slot.setIndex);
					const auto vertexIndex = elementIndices.at(primitiveVertexIndex);
					const auto& vertexElements = shape->vertices().vertexElementComponentsAt(slot.semantic, slot.setIndex);
					const auto& source = componentsAt(vertexElements, vertexIndex, slot.semantic, slot.shapeIndex);
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

	// Now compute the blend-shape vector-deltas by subtracting the blend-shape-base mesh from the blend-shape-targets
	if (meshShapes.size() > 1)
	{
		for (auto&& pair : m_table)
		{
			VertexBuffer& buffer = pair.second;
			VertexComponentsMap& compMap = buffer.componentsMap;

			for (auto&& slotCompPair: compMap)
			{
				auto& targetSlot = slotCompPair.first;

				if (targetSlot.shapeIndex.isBlendShapeIndex())
				{
					const VertexSlot mainSlot(ShapeIndex::main(), targetSlot.semantic, targetSlot.setIndex);
					const FloatVector& mainComponents = compMap.at(mainSlot);
					FloatVector& targetComponents = slotCompPair.second;
					const auto componentCount = mainComponents.size();
					assert(componentCount == targetComponents.size());
					for (size_t i=0; i<componentCount; ++i)
					{
						targetComponents[i] -= mainComponents[i];
					}
				}
			}
		}
	}

	CONSTRUCTOR_END();
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

	dump_iterable(out, "indices", obj.indices, obj.indices.size() / obj.vertexToIndexMapping.size(), 0);

	out << "," << endl;

	dump_iterable(out, "components", obj.componentsMap, 1);

	out << undent << '}';

	return out;
}

