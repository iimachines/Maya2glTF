#include "externals.h"
#include "MeshVertices.h"

MeshVertices::MeshVertices(MFnMesh& mesh, const MSpace::Space space)
{
	mesh.getPoints(m_Positions, space);
	mesh.getNormals(m_Normals, space);
	mesh.getTangents(m_Tangents, space);
	mesh.getColors(m_Colors);

	// UVs. These are not interleaved in Maya, so we have to do it ourselves...
	{
		MString uvSetName;
		mesh.getCurrentUVSetName(uvSetName);

		MFloatArray uArray;
		MFloatArray vArray;
		mesh.getUVs(uArray, vArray, &uvSetName);

		assert(uArray.length() == vArray.length());
		const auto uiSize = uArray.length();
		m_TexCoords.resize(uiSize);
		for (unsigned int ui = 0; ui < uiSize; ui++)
		{
			auto uv = m_TexCoords[ui];
			uv[0] = uArray[ui];
			uv[1] = 1.0f - vArray[ui];
		}
	}
}

MeshVertices::~MeshVertices()
{
}

