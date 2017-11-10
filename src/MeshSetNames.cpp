#include "externals.h"
#include "MeshSetNames.h"
#include "MayaException.h"
#include "dump.h"

MeshSetNames::MeshSetNames(const MFnMesh& mesh)
{
	THROW_ON_FAILURE(mesh.getColorSetNames(m_colors));
	THROW_ON_FAILURE(mesh.getUVSetNames(m_texCoords));
}


MeshSetNames::~MeshSetNames()
{
}

void MeshSetNames::dump(const std::string& name, const std::string& indent) const
{
	cout << indent << name << ": {" << endl;

	const auto subIndent = indent + "\t";
	
	dump_array("colors", m_colors, subIndent);
	cout << "," << endl;
	
	dump_array("texCoords", m_texCoords, subIndent);
	cout << endl;

	cout << indent << "}" << endl;
}
