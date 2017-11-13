#include "externals.h"
#include "MeshRenderable.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "dump.h"

MeshRenderable::MeshRenderable(
	const int shaderIndex,
	const MeshSemantics& meshSemantics,
	const MeshVertices& meshVertices,
	const MeshIndices& meshIndices)
	: shaderIndex(shaderIndex)
{
	std::map<IndexVector, Index> drawableComponentIndexMap;

	const auto& shaderMap = meshIndices.primitiveToShaderIndexMap();
	const auto& indicesTable = meshIndices.table();
	const auto& componentsTable = meshVertices.table();

	const auto primitiveCount = meshIndices.primitiveToShaderIndexMap().size();

	const auto keySize = meshSemantics.totalSetCount();

	IndexVector key;
	key.reserve(keySize);

	int lastVertexIndex = -1;

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
		if (shaderMap[primitiveIndex] != shaderIndex)
		{
			// This primitive does not belong to the shader, skip it.
			componentIndex += componentsPerPrimitive;
			continue;
		}

		// Add each component of  the primitive.
		for (int counter = componentsPerPrimitive; --counter >= 0; ++componentIndex)
		{
			key.clear();

			for (auto && indicesPerSet : indicesTable)
			{
				for (auto && indices : indicesPerSet)
				{
					key.push_back(indices[componentIndex]);
				}
			}

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

						target.insert(target.end(),
							source.begin() + groupSize * sourceIndex,
							source.begin() + groupSize * (sourceIndex + 1));
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

void MeshRenderable::dump(const std::string& name, const std::string& indent) const
{
	const auto subIndent = indent + "\t";
	cout << indent << quoted(name) << ": {" << endl;
	cout << subIndent << std::quoted("shaderIndex") << ":" << std::to_string(shaderIndex) << "," << endl;
	dump_table("vertices", m_table, subIndent);
	cout << "," << endl;
	dump_iterable("indices", m_indices, subIndent);
	cout << "," << endl;
	cout << indent << "}";
}
