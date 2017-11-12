#include "externals.h"
#include "MeshDrawable.h"
#include "dump.h"


MeshDrawable::MeshDrawable(const Mesh& mesh)
{
	std::map<IndexVector, Index> drawableComponentIndexMap;

	const auto& meshSemantics = mesh.semantics();
	const auto& meshVertices = mesh.vertices();
	const auto& meshIndices = mesh.indices();

	const auto& indicesTable = meshIndices.table();
	const auto& componentsTable = meshVertices.table();

	const auto primitiveComponentCount = indicesTable.at(Semantic::POSITION).at(0).size();

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
	for (int primitiveComponentIndex = 0; primitiveComponentIndex < primitiveComponentCount; ++primitiveComponentIndex)
	{
		key.clear();

		for (auto && indicesPerSet : indicesTable)
		{
			for (auto && indices : indicesPerSet)
			{
				key.push_back(indices[primitiveComponentIndex]);
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
				const auto groupSize = Semantic::components(semanticKind);
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


MeshDrawable::~MeshDrawable()
{
}

void MeshDrawable::dump(const std::string& name, const std::string& indent) const
{
	const auto subIndent = indent + "\t";
	cout << indent << quoted(name) << ": {" << endl;
	dump_table("vertices", m_table, subIndent);
	cout << "," << endl;
	dump_iterable("indices", m_indices, subIndent);
	cout << "," << endl;
	cout << indent << "}";
}
