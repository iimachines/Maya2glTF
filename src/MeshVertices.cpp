#include "externals.h"
#include "MeshVertices.h"
#include "MayaException.h"
#include "Dump.h"
#include "spans.h"

MeshVertices::MeshVertices(const MeshSemantics& semantics, const MFnMesh& mesh, const MSpace::Space space)
{
	// Get points
	mesh.getPoints(m_positions, space);

	const auto positionsSpan = reinterpret_span<float>(span(m_positions));
	m_table.at(Semantic::POSITION).push_back(positionsSpan);

	// Get normals
	mesh.getNormals(m_normals, space);

	const auto normalsSpan = reinterpret_span<float>(span(m_normals));
	m_table.at(Semantic::NORMAL).push_back(normalsSpan);

	// Get color sets.
	for (auto&& semantic: semantics.descriptions(Semantic::COLOR))
	{
		auto& colors = m_colorSets[semantic.setIndex];
		THROW_ON_FAILURE(mesh.getColors(colors, &semantic.setName));
		
		const auto colorsSpan = reinterpret_span<float>(span(colors));
		m_table.at(Semantic::COLOR).push_back(colorsSpan);
	}

	// Get UV sets.
	// These are not interleaved in Maya, so we have to do it ourselves...
	for (auto&& semantic : semantics.descriptions(Semantic::TEXCOORD))
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

		const auto uvSpan = reinterpret_span<float>(span(uvSet));
		m_table.at(Semantic::TEXCOORD).push_back(uvSpan);
	}
}

MeshVertices::~MeshVertices()
{
}

void MeshVertices::dump(const std::string& name, const std::string& indent) const
{
	dump_table(name, m_table, indent);
}

