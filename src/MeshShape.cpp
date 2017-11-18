#include "externals.h"
#include "MeshShape.h"
#include "MayaException.h"

MeshShape::MeshShape(const MFnMesh& fnMesh, const bool isBlendShape): isBlendShape(isBlendShape)
{
	m_semantics.reset(new MeshSemantics(fnMesh, isBlendShape));
	m_vertices.reset(new MeshVertices(*m_semantics, fnMesh));
	m_indices.reset(new MeshIndices(*m_semantics, fnMesh));
}

MeshShape::~MeshShape()
{
}

void MeshShape::dump(const std::string& name, const std::string& indent) const
{
	cout << indent << quoted(name) << ": {" << endl;
	const auto subIndent = indent + "\t";
	cout << subIndent << "isBlendShape: " << isBlendShape << ", " << endl;
	m_semantics->dump("semantics", subIndent);
	cout << "," << endl;
	m_vertices->dump("vertices", subIndent);
	cout << "," << endl;
	m_indices->dump("indices", subIndent);
	cout << "," << endl;
	cout << indent << "}" << endl;
}

