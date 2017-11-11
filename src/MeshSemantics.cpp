#include "externals.h"
#include "MeshSemantics.h"
#include "MayaException.h"

void MeshSemantic::dump(const std::string& indent) const
{
	const auto subIndent = indent + "\t";

	cout << indent << std::quoted(Semantic::name(kind)) << ": {" << endl;

	cout << subIndent << std::quoted("setName") << ": " << std::quoted(setName.asChar()) << "," << endl;
	cout << subIndent << std::quoted("setIndex") << ": " << setIndex << "," << endl;
	cout << subIndent << std::quoted("elementCount") << ": " << elementCount << endl;

	cout << indent << "}";
}

MeshSemantics::MeshSemantics(const MFnMesh& mesh)
{
	MStatus status;

	m_items[Semantic::POSITION].push_back(
		MeshSemantic(Semantic::POSITION, 0, "", mesh.numVertices(&status)));
	THROW_ON_FAILURE(status);

	m_items[Semantic::NORMAL].push_back(
		MeshSemantic(Semantic::NORMAL, 0, "", mesh.numNormals(&status)));
	THROW_ON_FAILURE(status);

	MStringArray colorSetNames;
	THROW_ON_FAILURE(mesh.getColorSetNames(colorSetNames));

	for (unsigned i = 0; i < colorSetNames.length(); ++i)
	{
		m_items[Semantic::COLOR].push_back(
			MeshSemantic(Semantic::COLOR, i, colorSetNames[i].asChar(), mesh.numColors(colorSetNames[i], &status)));
		THROW_ON_FAILURE(status);
	}

	MStringArray uvSetNames;
	THROW_ON_FAILURE(mesh.getUVSetNames(uvSetNames));

	for (unsigned  i = 0; i < uvSetNames.length(); ++i)
	{
		m_items[Semantic::TEXCOORD].push_back(
			MeshSemantic(Semantic::TEXCOORD, i, uvSetNames[i].asChar(), mesh.numUVs(uvSetNames[i], &status)));
		THROW_ON_FAILURE(status);
	}
}


MeshSemantics::~MeshSemantics()
{
}

void MeshSemantics::dump(const std::string& name, const std::string& indent) const
{
	const auto subIndent = indent + "\t";

	cout << indent << quoted(name) << ": {" << endl;

	for (auto&& semantics : m_items)
	{
		for (auto&& semantic : semantics)
		{
			semantic.dump(subIndent);
			cout << "," << endl;
		}
	}

	cout << indent << "}";
}
