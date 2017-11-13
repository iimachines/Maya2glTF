#include "externals.h"
#include "MeshVertices.h"
#include "MayaException.h"
#include "Dump.h"
#include "spans.h"

MeshVertices::MeshVertices(const MeshSemantics& semantics, const MFnMesh& mesh, const MSpace::Space space)
{
	MStatus status;

	// Get points
	const int numPoints = mesh.numVertices(&status);
	THROW_ON_FAILURE(status);
	m_positions.reserve(numPoints);
	for (int i = 0; i < numPoints; ++i)
	{
		MPoint p;
		mesh.getPoint(i, p, space);
		m_positions.push_back({ static_cast<float>(p.x), static_cast<float>(p.y), static_cast<float>(p.z) });
	}

	const auto positionsSpan = reinterpret_span<float>(span(m_positions));
	m_table.at(Semantic::POSITION).push_back(positionsSpan);

	// Get normals
	MFloatVectorArray normals;
	THROW_ON_FAILURE(mesh.getNormals(normals));
	const int numNormals = normals.length();
	m_normals.reserve(numNormals);
	for (int i = 0; i < numNormals; ++i)
	{
		const auto& n = normals[i];
		m_normals.push_back({ n.x, n.y, n.z });
	}

	const auto normalsSpan = reinterpret_span<float>(span(m_normals));
	m_table.at(Semantic::NORMAL).push_back(normalsSpan);

	// Get color sets.
	for (auto&& semantic : semantics.descriptions(Semantic::COLOR))
	{
		const int numColors = mesh.numColors(semantic.setName, &status);
		THROW_ON_FAILURE(status);

		auto& colors = m_colorSets[semantic.setIndex];
		colors.reserve(numColors);
		for (int i = 0; i < numColors; ++i)
		{
			MColor c;
			mesh.getColor(i, c, &semantic.setName);
			colors.push_back({ c.r, c.g, c.b, c.a });
		}

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
			uvArray[1] = vArray[uIndex];
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

