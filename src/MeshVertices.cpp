#include "externals.h"
#include "MeshVertices.h"
#include "MayaException.h"
#include "Dump.h"

MeshVertices::MeshVertices(const MeshSemantics& semantics, const MFnMesh& mesh, const MSpace::Space space)
{
	mesh.getPoints(m_positions, space);
	mesh.getNormals(m_normals, space);

	// Get color sets.
	for (auto&& semantic: semantics.at(Semantic::COLOR))
	{
		THROW_ON_FAILURE(mesh.getColors(m_colorSets[semantic.setIndex], &semantic.setName));
	}

	// Get UV sets.
	// These are not interleaved in Maya, so we have to do it ourselves...
	for (auto&& semantic : semantics.at(Semantic::TEXCOORD))
	{
		MFloatArray uArray;
		MFloatArray vArray;
		THROW_ON_FAILURE(mesh.getUVs(uArray, vArray, &semantic.setName));

		assert(uArray.length() == vArray.length());
		const int uCount = uArray.length();

		auto& uvSet = m_uvSets[semantic.setIndex] = Float2Vector(uCount);
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
	cout << indent << quoted(name) << ": {" << endl;

	const auto subIndent = indent + "\t";

	dump_span<float>("POSITION", span(m_positions), subIndent);
	cout << "," << endl;

	dump_span<float>("NORMAL", span(m_normals), subIndent);
	cout << "," << endl;

	for (const auto& pair : m_uvSets)
		dump_span<float>("TEXCOORD_" + std::to_string(pair.first), span(pair.second), subIndent);

	if (!m_uvSets.empty()) 
		cout << "," << endl;

	for (const auto& pair : m_colorSets)
		dump_span<float>("COLOR_" + std::to_string(pair.first), span(pair.second), subIndent);

	cout << indent << "}";
}

