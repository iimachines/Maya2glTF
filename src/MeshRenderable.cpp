#include "externals.h"
#include "MeshRenderable.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "dump.h"
#include "DagHelper.h"
#include "MeshShape.h"
#include "MeshBlendShapes.h"
#include "MeshVertexComponentMappings.h"

MeshRenderable::MeshRenderable(
	const int shaderIndex,
	const MeshVertexComponentMappings& vertexSignatures)
	: shaderIndex(shaderIndex)
	, vertexSignatures(vertexSignatures)
{
	MStatus status;

	const auto& meshShape = vertexSignatures.shape;
	const auto* maybeBlendShapes = vertexSignatures.maybeBlendShapes;

	const auto& meshIndices = meshShape.indices();
	const auto& meshVertices = meshShape.vertices();
	const auto& meshSemantics = meshShape.semantics();

	const MeshShading& shading = meshIndices.shadingPerInstance().at(meshInstanceIndex);

	m_shaderGroup = shading.shaderGroups[shaderIndex];

	std::map<IndexVector, Index> vertexMap;

	const auto& shaderMap = shading.primitiveToShaderIndexMap;
	const auto& indicesTable = meshIndices.table();
	const auto& verticesTable = meshVertices.table();

	const auto primitiveCount = shaderMap.size();

	auto keySize = meshSemantics.totalSetCount();

	const auto hasBlendShapes = maybeBlendShapes && !maybeBlendShapes->empty();

	// Verify that all blend-shapes have the same "topology"
	if (hasBlendShapes)
	{
		const auto baseShape = maybeBlendShapes->baseShape();
		if (baseShape->indices().primitiveCount() != primitiveCount)
			throw std::runtime_error(formatted("Base shape '%s' has different topology from '%s'!",
				meshShape.dagPath().fullPathName().asChar(), baseShape->dagPath().fullPathName().asChar()));

		for (auto&& entry : maybeBlendShapes->entries())
		{
			const auto& shape = entry->shape;
			if (shape.indices().primitiveCount() != primitiveCount)
				throw std::runtime_error(formatted("Blend shape '%s' has different topology from '%s'!",
					meshShape.dagPath().fullPathName().asChar(), shape.dagPath().fullPathName().asChar()));

			keySize += shape.semantics().totalSetCount();
		}
	}

	IndexVector key;
	key.reserve(keySize);

	int lastVertexIndex = -1;

	uint64 vertexMask = 0;

	// Allocate drawable component vectors
	for (auto semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);
		const auto& inputVerticesPerSet = verticesTable.at(semanticKind);
		auto& outputVerticesPerSet = m_table.at(semanticKind);

		for (auto setIndex = 0; setIndex < inputVerticesPerSet.size(); ++setIndex)
		{
			const auto& source = inputVerticesPerSet[setIndex];

			FloatVector target;
			target.reserve(source.size() * 2);
			outputVerticesPerSet.push_back(target);
		}
	}

	if (hasBlendShapes)
	{
		// Allocate delta component vectors
		const auto& entries = maybeBlendShapes->entries();
		for (auto targetIndex = 0; targetIndex < entries.size(); ++targetIndex)
		{
			for (auto semanticIndex = 0; semanticIndex < Semantic::MORPH_COUNT; ++semanticIndex)
			{
				const auto semanticKind = Semantic::from(semanticIndex);
				auto& targetDeltasPerShape = m_deltasTable.at(semanticKind);
				targetDeltasPerShape.push_back(FloatVector());
			}
		}
	}

	// Merge components
	auto primitiveVertexIndex = 0;

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

