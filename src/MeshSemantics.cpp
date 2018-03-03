#include "externals.h"
#include "MeshSemantics.h"
#include "MayaException.h"
#include "IndentableStream.h"

void VertexElementSetDescription::dump(class IndentableStream& out, const std::string& name) const
{
	out << std::quoted(name) << ": {" << endl << indent;

	out << std::quoted("setName") << ": " << std::quoted(setName.asChar()) << "," << endl;
	out << std::quoted("setIndex") << ": " << setIndex << "," << endl;
	out << std::quoted("elementCount") << ": " << elementCount << endl;

	out << undent << '}';
}

MeshSemantics::MeshSemantics(const MFnMesh& mesh, const bool isBlendShape)
{
	CONSTRUCTOR_BEGIN();

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

	CONSTRUCTOR_END();
}


MeshSemantics::~MeshSemantics()
{
}

void MeshSemantics::dump(class IndentableStream& out, const std::string& name) const
{
	out << quoted(name) << ": {" << endl << indent;

	JsonSeparator sep(",\n");

	for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);

		for (auto&& semantic : m_table.at(semanticKind))
		{
			out << sep;
			semantic.dump(out, Semantic::name(semanticKind));
		}
	}

	out << endl << undent << '}';
}
