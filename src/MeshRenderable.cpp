#include "externals.h"
#include "MeshRenderable.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "dump.h"
#include "DagHelper.h"
#include "MeshShape.h"
#include "MeshBlendShapes.h"

MeshRenderable::MeshRenderable(
	const int meshInstanceIndex,
	const int meshShaderIndex, 
	const MeshShape& meshShape,
	const MeshBlendShapes* maybeBlendShapes)
	: meshInstanceIndex(meshInstanceIndex)
	, meshShaderIndex(meshShaderIndex)
{
	MStatus status;

	const auto& meshIndices = meshShape.indices();
	const auto& meshVertices = meshShape.vertices();
	const auto& meshSemantics = meshShape.semantics();

	const MeshShading& shading = meshIndices.shadingPerInstance().at(meshInstanceIndex);

	m_shaderGroup = shading.shaderGroups[meshShaderIndex];

	std::map<IndexVector, Index> drawableComponentIndexMap;

	const auto& shaderMap = shading.primitiveToShaderIndexMap;
	const auto& indicesTable = meshIndices.table();
	const auto& componentsTable = meshVertices.table();

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

		for (auto&& entry: maybeBlendShapes->entries())
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
		const auto& sourceComponentsPerSet = componentsTable.at(semanticKind);
		auto& targetComponentsPerSet = m_table.at(semanticKind);

		for (auto setIndex = 0; setIndex < sourceComponentsPerSet.size(); ++setIndex)
		{
			const auto& source = sourceComponentsPerSet[setIndex];

			FloatVector target;
			target.reserve(source.size() * 2);
			targetComponentsPerSet.push_back(target);
		}
	}

	// Merge components
	int componentIndex = 0;
	const int componentsPerPrimitive = 3;

	for (int primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex)
	{
		if (shaderMap[primitiveIndex] != meshShaderIndex)
		{
			// This primitive does not belong to the shader, skip it.
			componentIndex += componentsPerPrimitive;
			continue;
		}

		// Add each component of the primitive.
		for (int counter = componentsPerPrimitive; --counter >= 0; ++componentIndex)
		{
			key.clear();

			uint64 keyMask = 0;

			for (auto && indicesPerSet : indicesTable)
			{
				for (auto && indices : indicesPerSet)
				{
					const auto index = indices[componentIndex];
					key.push_back(index);

					keyMask <<= 1;
					keyMask |= index >= 0;
				}
			}

			// Also add blend shapes
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
							const auto index = indices[componentIndex];
							key.push_back(index);

							keyMask <<= 1;
							keyMask |= index >= 0;
						}
					}
				}
			}

			if (vertexMask && vertexMask != keyMask)
				throw std::exception("Mesh seems to have invalid set assignments");

			vertexMask = keyMask;

			int vertexIndex;

			const auto foundIt = drawableComponentIndexMap.find(key);

			if (foundIt != drawableComponentIndexMap.end())
			{
				// Reuse the vertex
				vertexIndex = foundIt->second;
			}
			else
			{
				// Create a new vertex
				vertexIndex = ++lastVertexIndex;

				drawableComponentIndexMap[key] = vertexIndex;

				auto keyIndex = 0;

				for (auto semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
				{
					const auto semanticKind = Semantic::from(semanticIndex);
					const auto groupSize = Semantic::dimension(semanticKind);
					const auto& sourceComponentsPerSet = componentsTable.at(semanticKind);
					auto& targetComponentsPerSet = m_table.at(semanticKind);

					for (auto setIndex = 0; setIndex < sourceComponentsPerSet.size(); ++setIndex)
					{
						const auto& source = sourceComponentsPerSet[setIndex];
						auto& target = targetComponentsPerSet[setIndex];

						const auto sourceIndex = key[keyIndex++];

						if (sourceIndex >= 0)
						{
							target.insert(target.end(),
								source.begin() + groupSize * sourceIndex,
								source.begin() + groupSize * (sourceIndex + 1));
						}
					}
				}

				// Also add blend shape deltas
				if (hasBlendShapes)
				{
					const auto baseShape = maybeBlendShapes->baseShape();
					const auto& baseComponentsTable = baseShape->vertices().table();
					const auto& baseIndicesTable = baseShape->indices().table();

					const auto& entries = maybeBlendShapes->entries();

					for (auto targetIndex = 0; targetIndex < entries.size(); ++targetIndex)
					{
						const auto& shape = entries.at(targetIndex)->shape;
						const auto& shapeComponentsTable = shape.vertices().table();
						const auto& shapeIndicesTable = shape.indices().table();

						for (auto semanticIndex = 0; semanticIndex < Semantic::MORPH_COUNT; ++semanticIndex)
						{
							const auto semanticKind = Semantic::from(semanticIndex);
							const auto groupSize = Semantic::dimension(semanticKind);

							const auto& baseIndicesPerSet = baseIndicesTable.at(semanticIndex);
							const auto& shapeIndicesPerSet = shapeIndicesTable.at(semanticIndex);

							const auto& baseComponentsPerSet = baseComponentsTable.at(semanticKind);
							const auto& sourceComponentsPerSet = shapeComponentsTable.at(semanticKind);

							auto& targetComponentsPerShape = m_deltasTable.at(semanticKind);

							const auto& shapeSource = sourceComponentsPerSet.at(0);
							const auto& baseSource = baseComponentsPerSet.at(0);

							const auto baseSourceIndex = baseIndicesPerSet.at(0).at(componentIndex);
							const auto shapeSourceIndex = shapeIndicesPerSet.at(0).at(componentIndex);
							assert(baseSourceIndex >= 0);
							assert(shapeSourceIndex >= 0);

							// TODO: Preallocate!
							if (targetComponentsPerShape.size() == 0)
								targetComponentsPerShape.push_back(FloatVector());

							auto& target = targetComponentsPerShape.at(targetIndex);

							const auto offset = target.size();

							target.insert(target.end(),
								shapeSource.begin() + groupSize * shapeSourceIndex,
								shapeSource.begin() + groupSize * (shapeSourceIndex + 1));

							// Subtract base shape
							auto itBase = baseSource.begin() + groupSize * shapeSourceIndex;
							auto itTarget = target.begin() + offset;
							const auto itEnd = target.end();
							while (itTarget<itEnd)
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
	cout << subIndent << std::quoted("meshShaderIndex") << ":" << std::to_string(meshShaderIndex) << "," << endl;
	dump_table("vertices", m_table, subIndent);
	cout << "," << endl;
	dump_iterable("indices", m_indices, subIndent);
	cout << "," << endl;
	dump_table("deltas", m_deltasTable, subIndent);
	cout << "," << endl;
	cout << indent << "}";
}

