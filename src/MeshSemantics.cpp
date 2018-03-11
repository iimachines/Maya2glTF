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

MeshSemantics::MeshSemantics(const MFnMesh& mesh)
{
	CONSTRUCTOR_BEGIN();

	MStatus status;

	// NOTE: Currently we fetch all the semantics, even for blend-shapes, since we might want to included texture coordinates or colors into blend-shapes at some point.
	m_table[Semantic::POSITION].emplace_back(Semantic::POSITION, 0, "", mesh.numVertices(&status));
	THROW_ON_FAILURE(status);

	m_table[Semantic::NORMAL].emplace_back(Semantic::NORMAL, 0, "", mesh.numNormals(&status));
	THROW_ON_FAILURE(status);

	MStringArray colorSetNames;
	THROW_ON_FAILURE(mesh.getColorSetNames(colorSetNames));

	for (unsigned i = 0; i < colorSetNames.length(); ++i)
	{
		m_table[Semantic::COLOR].emplace_back(Semantic::COLOR, i, colorSetNames[i].asChar(), mesh.numColors(colorSetNames[i], &status));
		THROW_ON_FAILURE(status);
	}

	MStringArray uvSetNames;
	THROW_ON_FAILURE(mesh.getUVSetNames(uvSetNames));

	for (unsigned i = 0; i < uvSetNames.length(); ++i)
	{
		m_table[Semantic::TEXCOORD].emplace_back(Semantic::TEXCOORD, i, uvSetNames[i].asChar(), mesh.numUVs(uvSetNames[i], &status));
		m_table[Semantic::TANGENT].emplace_back(Semantic::TANGENT, i, uvSetNames[i].asChar(), mesh.numUVs(uvSetNames[i], &status));
	}

	CONSTRUCTOR_END();
}


MeshSemantics::~MeshSemantics() = default;

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
