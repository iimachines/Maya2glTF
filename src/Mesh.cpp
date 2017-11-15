#include "externals.h"
#include "Mesh.h"
#include "MayaException.h"

Mesh::Mesh(const MDagPath& dagPath) : m_dagPath(dagPath)
{
	MStatus status;

	MFnMesh fnMesh(dagPath, &status);
	THROW_ON_FAILURE(status);

	m_semantics.reset(new MeshSemantics(fnMesh));
	m_vertices.reset(new MeshVertices(*m_semantics, fnMesh));
	m_indices.reset(new MeshIndices(*m_semantics, fnMesh));

	auto& shaderUsages = m_indices->shaderUsages();

	for (auto shaderIndex=0; shaderIndex<shaderUsages.size(); ++shaderIndex)
	{
		// If the shader is not used by any primitive, skip it
		if (shaderUsages[shaderIndex])
		{
			m_renderables.emplace_back(
				std::make_unique<MeshRenderable>(shaderIndex, *m_semantics, *m_vertices, *m_indices));
		}
	}
}

Mesh::~Mesh()
{
}

void Mesh::dump(const std::string& name, const std::string& indent) const
{
	const auto& shaders = m_indices->shaderGroups();

	cout << indent << quoted(name) << ": {" << endl;
	const auto subIndent = indent + "\t";
	m_semantics->dump("semantics", subIndent);
	cout << "," << endl;
	m_vertices->dump("vertices", subIndent);
	cout << "," << endl;
	m_indices->dump("indices", subIndent);
	cout << "," << endl;
	cout << subIndent << std::quoted("renderables") << ": [" << endl;
	const auto subIndent2 = subIndent + "\t";
	for (auto && renderable: m_renderables)
	{
		renderable->dump(subIndent2);
		cout << "," << endl;
	}
	cout << subIndent << "]" << endl;
	cout << indent << "}" << endl;
}

