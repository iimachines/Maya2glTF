#include "externals.h"
#include "Mesh.h"
#include "MayaException.h"

Mesh::Mesh(MDagPath dagPath):m_dagPath(dagPath)
{
	MStatus status;
	MFnMesh fnMesh(dagPath, &status);
	THROW_ON_FAILURE(status);

	m_setNames.reset(new MeshSetNames(fnMesh));
	m_vertices.reset(new MeshVertices(*m_setNames, fnMesh));
	m_indices.reset(new MeshIndices(*m_setNames, fnMesh));
}

Mesh::~Mesh()
{
}

void Mesh::dump(const std::string& name, const std::string& indent) const
{
	cout << indent << name << ": {" << endl;
	const auto subIndent = indent + "\t";
	m_setNames->dump("setNames", subIndent);
	cout << "," << endl;
	m_vertices->dump("vertices", subIndent);
	cout << "," << endl;
	m_indices->dump("indices", subIndent);
	cout << endl;
	cout << indent << "}" << endl;
}

