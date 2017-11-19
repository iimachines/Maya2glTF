#include "externals.h"
#include "MeshRenderable.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "dump.h"
#include "DagHelper.h"
#include "MeshShape.h"
#include "MeshBlendShapes.h"
#include "MeshShapesIndices.h"
#include "MeshShapesVertexIndexer.h"

MeshRenderable::MeshRenderable(
	const int shaderIndex,
	const VertexSignature& vertexSignature,
	const MeshShapesVertexIndexer& vertexComponentIndices)
	: shaderIndex(shaderIndex)
	, vertexSignature(vertexSignature)
	, vertexComponentIndices(vertexComponentIndices)
{
	MStatus status;

	const auto& shapesIndices = vertexComponentIndices.meshShapesIndices;
	const auto& vertexComponentIndicesMapping = vertexComponentIndices.mapping();
	const auto& vertexComponentIndices = vertexComponentIndicesMapping.at(vertexSignature);

	const auto& indicesCollection = shapesIndices.collection();
	const auto& indicesOffsets = shapesIndices.offsets();

	const auto& meshShape = shapesIndices.mainShape;

	const auto& meshIndices = meshShape.indices();
	const auto& meshVertices = meshShape.vertices();
	const auto& meshSemantics = meshShape.semantics();

	const auto hasBlendShapes = shapesIndices.hasBlendShapes();

	const MeshShading& shading = meshIndices.shadingPerInstance().at(vertexComponentIndices.instanceIndex);

	m_shaderGroup = shading.shaderGroups[shaderIndex];

	std::map<IndexVector, Index> vertexMap;

	const auto& shaderMap = shading.primitiveToShaderIndexMap;
	const auto& indicesTable = meshIndices.table();
	const auto& verticesTable = meshVertices.table();

	const auto primitiveCount = shaderMap.size();

	int lastVertexIndex = -1;

	// Allocate component vectors
	for (auto shapeIndex = 0; shapeIndex < indicesCollection.size(); ++shapeIndex)
	{
		const auto& shapeIndicesTable = indicesCollection.at(shapeIndex)->table();
		for (auto semanticIndex=0; semanticIndex<shapeIndicesTable.size(); ++semanticIndex)
		{
			const auto & indicesPerSet = shapeIndicesTable[semanticIndex];

			for (auto&& indices: indicesPerSet)
			{
				if (shapeIndex == indicesOffsets.mainMeshOffset)
				{
					auto& outputVertexComponentsPerSet = m_table.at(semanticIndex);
					outputVertexComponentsPerSet.push_back(FloatVector());
				}
				else if (indicesOffsets.isBlendShapeOffset(shapeIndex))
				{
					auto& outputDeltasPerShape = m_deltasTable.at(semanticIndex);
					outputDeltasPerShape.push_back(FloatVector());
				}
			}
		}
	}

	// Merge vertex components 

	const auto perPrimitiveVertexCount = meshIndices.perPrimitiveVertexCount();

	for (int primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex)
	{
		if (shaderMap[primitiveIndex] != shaderIndex)
		{
			// This primitive is not shaded, skip it.
			primitiveVertexIndex += perPrimitiveVertexCount;
			continue;
		}

		// Add each vertex of the primitive.
		for (int counter = perPrimitiveVertexCount; --counter >= 0; ++primitiveVertexIndex)
		{
			// Build a key of indices. 
			// If a vertex with the same key is already added, reuse it.
			// TODO: We should use a set of the vertices itself!
			key.clear();

			uint64 keyMask = 0;

			for (auto && indicesPerSet : indicesTable)
			{
				for (auto && indices : indicesPerSet)
				{
					const auto index = indices[primitiveVertexIndex];
					key.push_back(index);

					keyMask <<= 1;
					keyMask |= index >= 0;
				}
			}

			// Also add blend shapes indices to the key. 
			// The topology of the blend shapes must be exactly the same as the main mesh, 
			// ie if we split a vertex in the main mesh, 
			// we must also split it in the blend shapes.
			if (hasBlendShapes)
			{
				//const auto baseShape = maybeBlendShapes->baseShape();
				//for (auto && indicesPerSet : baseShape->indices().table())
				//{
				//	for (auto && indices : indicesPerSet)
				//	{
				//		const auto index = indices[componentIndex];
				//		key.push_back(index);

				//		keyMask <<= 1;
				//		keyMask |= index >= 0;
				//	}
				//}

				const auto& entries = maybeBlendShapes->entries();
				for (auto&& entry : entries)
				{
					const auto& shape = entry->shape;

					for (auto && indicesPerSet : shape.indices().table())
					{
						for (auto && indices : indicesPerSet)
						{
							const auto index = indices[primitiveVertexIndex];
							key.push_back(index);

							keyMask <<= 1;
							keyMask |= index >= 0;
						}
					}
				}
			}

			if (vertexMask && vertexMask != keyMask)
				throw std::runtime_error(formatted("Mesh seems to have invalid set assignments (0x%08X vs 0x%08X)"));

			vertexMask = keyMask;

			int vertexIndex;

			const auto foundIt = vertexMap.find(key);

			if (foundIt != vertexMap.end())
			{
				// Reuse the vertex
				vertexIndex = foundIt->second;
			}
			else
			{
				// Create a new vertex
				vertexIndex = ++lastVertexIndex;

				vertexMap[key] = vertexIndex;

				auto keyIndex = 0;

				for (auto semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
				{
					const auto semanticKind = Semantic::from(semanticIndex);
					const auto groupSize = Semantic::dimension(semanticKind);
					const auto& inputVerticesPerSet = verticesTable.at(semanticKind);
					auto& outputVerticesPerSet = m_table.at(semanticKind);

					for (auto setIndex = 0; setIndex < inputVerticesPerSet.size(); ++setIndex)
					{
						const auto& inputVertex = inputVerticesPerSet[setIndex];
						auto& outputVertex = outputVerticesPerSet[setIndex];

						const auto inputIndices = key[keyIndex++];

						if (inputIndices >= 0)
						{
							outputVertex.insert(outputVertex.end(),
								inputVertex.begin() + groupSize * inputIndices,
								inputVertex.begin() + groupSize * (inputIndices + 1));
						}
					}
				}

				// Also add blend shape deltas
				if (hasBlendShapes)
				{
					const auto baseShape = maybeBlendShapes->baseShape();
					const auto& baseVerticesTable = baseShape->vertices().table();
					const auto& baseIndicesTable = baseShape->indices().table();

					const auto& entries = maybeBlendShapes->entries();

					for (auto outputIndex = 0; outputIndex < entries.size(); ++outputIndex)
					{
						const auto& shape = entries.at(outputIndex)->shape;
						const auto& shapeVerticesTable = shape.vertices().table();
						const auto& shapeIndicesTable = shape.indices().table();

						for (auto semanticIndex = 0; semanticIndex < Semantic::MORPH_COUNT; ++semanticIndex)
						{
							const auto semanticKind = Semantic::from(semanticIndex);
							const auto groupSize = Semantic::dimension(semanticKind);

							const auto& baseIndicesPerSet = baseIndicesTable.at(semanticIndex);
							const auto& shapeIndicesPerSet = shapeIndicesTable.at(semanticIndex);

							const auto& baseVerticesPerSet = baseVerticesTable.at(semanticKind);
							const auto& shapeVerticesPerSet = shapeVerticesTable.at(semanticKind);

							auto& deltaVerticesPerSet = m_deltasTable.at(semanticKind);

							const auto& shapeVertex = shapeVerticesPerSet.at(0);
							const auto& baseVertex = baseVerticesPerSet.at(0);

							const auto baseVertexIndex = baseIndicesPerSet.at(0).at(primitiveVertexIndex);
							const auto shapeVertexIndex = shapeIndicesPerSet.at(0).at(primitiveVertexIndex);
							assert(baseVertexIndex >= 0);
							assert(shapeVertexIndex >= 0);

							auto& deltaVertex = deltaVerticesPerSet.at(outputIndex);

							const auto offset = deltaVertex.size();

							deltaVertex.insert(deltaVertex.end(),
								shapeVertex.begin() + groupSize * shapeVertexIndex,
								shapeVertex.begin() + groupSize * (shapeVertexIndex + 1));

							// Subtract base shape
							auto itBase = baseVertex.begin() + groupSize * baseVertexIndex;
							auto itTarget = deltaVertex.begin() + offset;
							const auto itEnd = deltaVertex.end();
							while (itTarget < itEnd)
							{
								*itTarget++ -= *itBase++;
							}
						}
					}
				}
			}

			m_indices.push_back(vertexIndex);
		}
	}
}


MeshRenderable::~MeshRenderable()
{
}

void MeshRenderable::dump(const std::string& indent) const
{
	const auto subIndent = indent + "\t";
	cout << indent << "{" << endl;
	cout << subIndent << std::quoted("shaderIndex") << ":" << std::to_string(shaderIndex) << "," << endl;
	dump_table("vertices", m_table, subIndent);
	cout << "," << endl;
	dump_iterable("indices", m_indices, subIndent);
	cout << "," << endl;
	dump_table("deltas", m_deltasTable, subIndent);
	cout << "," << endl;
	cout << indent << "}";
}

