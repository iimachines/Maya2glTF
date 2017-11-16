#include "externals.h"
#include "Mesh.h"
#include "MayaException.h"

Mesh::Mesh(const MDagPath& dagPath) : m_dagPath(dagPath)
{
	MStatus status;

	const MFnMesh fnMesh(dagPath, &status);
	THROW_ON_FAILURE(status);

	auto instanceNumber = dagPath.instanceNumber(&status);
	THROW_ON_FAILURE(status);

	m_semantics.reset(new MeshSemantics(fnMesh));
	m_vertices.reset(new MeshVertices(*m_semantics, fnMesh));
	m_indices.reset(new MeshIndices(*m_semantics, fnMesh));

	auto& shadingPerInstance = m_indices->shadingPerInstance();

	auto& shading = shadingPerInstance.at(instanceNumber);
	const auto shaderCount = shading.shaderCount();
	for (auto shaderIndex = 0; shaderIndex < shaderCount; ++shaderIndex)
	{
		// If the shader is not used by any primitive, skip it
		if (shading.isShaderUsed[shaderIndex])
		{
			auto renderable = std::make_unique<MeshRenderable>(instanceNumber, shaderIndex, *m_semantics, *m_vertices, *m_indices);
			if (renderable->indices().size())
			{
				m_renderables.emplace_back(move(renderable));
			}
		}
	}
}

Mesh::~Mesh()
{
}

void Mesh::dump(const std::string& name, const std::string& indent) const
{
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

