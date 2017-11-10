#include "externals.h"
#include "MeshVertices.h"
#include "MayaException.h"
#include "Dump.h"

MeshVertices::MeshVertices(const MeshSetNames& names, const MFnMesh& mesh, const MSpace::Space space)
{
	mesh.getPoints(m_positions, space);
	mesh.getNormals(m_normals, space);

	// Get color sets.
	const auto& colorSetNames = names.colors();
	const int colorSetCount = colorSetNames.length();
	for (auto index = 0; index < colorSetCount; ++index)
	{
		auto colorSetName = colorSetNames[index];
		THROW_ON_FAILURE(mesh.getColors(m_colorSets[index], &colorSetName));
	}

	// Get UV sets.
	// These are not interleaved in Maya, so we have to do it ourselves...
	const auto& uvSetNames = names.texCoords();
	const int uvSetCount = uvSetNames.length();
	for (auto index = 0; index < uvSetCount; ++index)
	{
		auto uvSetName = uvSetNames[index];

		MFloatArray uArray;
		MFloatArray vArray;
		THROW_ON_FAILURE(mesh.getUVs(uArray, vArray, &uvSetName));

		assert(uArray.length() == vArray.length());
		const int uCount = uArray.length();

		auto& uvSet = m_uvSets[index] = Float2Vector(uCount);
		for (auto uIndex = 0; uIndex < uCount; uIndex++)
		{
			auto& uvArray = uvSet[uIndex];
			uvArray[0] = uArray[uIndex];
			uvArray[1] = 1.0f - vArray[uIndex];
		}
	}
}

MeshVertices::~MeshVertices()
{
}

void MeshVertices::dump(const std::string& name, const std::string& indent) const
{
	cout << indent << name << ": {" << endl;

	const auto subIndent = indent + "\t";

	dump_span<float>("POSITION", span(m_positions), subIndent);
	cout << subIndent << "," << endl;

	dump_span<float>("NORMAL", span(m_normals), subIndent);
	cout << subIndent << "," << endl;

	for (const auto pair : m_uvSets)
		dump_span<float>("TEXCOORD_" + pair.first, span(pair.second), subIndent);

	if (!m_uvSets.empty()) 
		cout << subIndent << "," << endl;

	for (const auto pair : m_colorSets)
		dump_span<float>("COLOR_" + pair.first, span(pair.second), subIndent);

	cout << indent << "}" << endl;
}

