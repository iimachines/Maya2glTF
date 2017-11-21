#include "externals.h"
#include "MeshSemantics.h"
#include "MayaException.h"

void VertexElementSetDescription::dump(const std::string& name, const std::string& indent) const
{
	const auto subIndent = indent + "\t";

	cout << indent << std::quoted(name) << ": {" << endl;

	cout << subIndent << std::quoted("setName") << ": " << std::quoted(setName.asChar()) << "," << endl;
	cout << subIndent << std::quoted("setIndex") << ": " << setIndex << "," << endl;
	cout << subIndent << std::quoted("elementCount") << ": " << elementCount << endl;

	cout << indent << "}";
}

MeshSemantics::MeshSemantics(const MFnMesh& mesh, const bool isBlendShape)
{
	MStatus status;

	m_table[Semantic::POSITION].push_back(
		VertexElementSetDescription(Semantic::POSITION, 0, "", mesh.numVertices(&status)));
	THROW_ON_FAILURE(status);

	m_table[Semantic::NORMAL].push_back(
		VertexElementSetDescription(Semantic::NORMAL, 0, "", mesh.numNormals(&status)));
	THROW_ON_FAILURE(status);

	if (!isBlendShape)
	{
		MStringArray colorSetNames;
		THROW_ON_FAILURE(mesh.getColorSetNames(colorSetNames));

		for (unsigned i = 0; i < colorSetNames.length(); ++i)
		{
			m_table[Semantic::COLOR].push_back(
				VertexElementSetDescription(Semantic::COLOR, i, colorSetNames[i].asChar(), mesh.numColors(colorSetNames[i], &status)));
			THROW_ON_FAILURE(status);
		}

		MStringArray uvSetNames;
		THROW_ON_FAILURE(mesh.getUVSetNames(uvSetNames));

		for (unsigned i = 0; i < uvSetNames.length(); ++i)
		{
			m_table[Semantic::TEXCOORD].push_back(
				VertexElementSetDescription(Semantic::TEXCOORD, i, uvSetNames[i].asChar(), mesh.numUVs(uvSetNames[i], &status)));
			m_table[Semantic::TANGENT].push_back(
				VertexElementSetDescription(Semantic::TANGENT, i, uvSetNames[i].asChar(), mesh.numUVs(uvSetNames[i], &status)));
		}
	}
}


MeshSemantics::~MeshSemantics()
{
}

void MeshSemantics::dump(const std::string& name, const std::string& indent) const
{
	const auto subIndent = indent + "\t";

	cout << indent << quoted(name) << ": {" << endl;

	for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);

		for (auto&& semantic : m_table.at(semanticKind))
		{
			semantic.dump(Semantic::name(semanticKind), subIndent);
			cout << "," << endl;
		}
	}

	cout << indent << "}";
}
