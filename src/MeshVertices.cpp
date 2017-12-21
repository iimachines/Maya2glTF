#include "externals.h"
#include "MeshVertices.h"
#include "MayaException.h"
#include "Dump.h"
#include "spans.h"
#include "DagHelper.h"
#include "IndentableStream.h"

MeshVertices::MeshVertices(const MeshSemantics& semantics, const MFnMesh& mesh, const MSpace::Space space)
{
	MStatus status;

	// Get points
	MPointArray mPoints;
	THROW_ON_FAILURE(mesh.getPoints(mPoints, space));
	const int numPoints = mPoints.length();
	m_positions.reserve(numPoints);

	for (int i = 0; i < numPoints; ++i)
	{
		const auto& p = mPoints[i];
		m_positions.push_back({static_cast<float>(p.x), static_cast<float>(p.y), static_cast<float>(p.z)});
	}

	const auto positionsSpan = reinterpret_span<float>(span(m_positions));
	m_table.at(Semantic::POSITION).push_back(positionsSpan);

	// Get normals
	auto oppositePlug = mesh.findPlug("opposite", true, &status);
	THROW_ON_FAILURE(status);

	bool shouldFlipNormals = false;
	status = oppositePlug.getValue(shouldFlipNormals);
	THROW_ON_FAILURE(status);

	// TODO: When flipping normals, we should also flip the winding
	const float normalSign = shouldFlipNormals ? -1.0f : 1.0f;

	MFloatVectorArray mNormals;
	THROW_ON_FAILURE(mesh.getNormals(mNormals, space));
	const int numNormals = mNormals.length();
	m_normals.reserve(numNormals);
	for (int i = 0; i < numNormals; ++i)
	{
		const auto& n = mNormals[i];
		m_normals.push_back({normalSign * n.x, normalSign * n.y, normalSign * n.z});
	}

	const auto normalsSpan = reinterpret_span<float>(span(m_normals));
	m_table.at(Semantic::NORMAL).push_back(normalsSpan);

	// Get color sets.
	for (auto&& semantic : semantics.descriptions(Semantic::COLOR))
	{
		MColorArray mColors;
		THROW_ON_FAILURE(mesh.getColors(mColors, &semantic.setName));

		const int numColors = mColors.length();
		THROW_ON_FAILURE(status);

		auto& colors = m_colorSets[semantic.setIndex];
		colors.reserve(numColors);
		for (int i = 0; i < numColors; ++i)
		{
			const auto& c = mColors[i];;
			colors.push_back({c.r, c.g, c.b, c.a});
		}

		const auto colorsSpan = reinterpret_span<float>(span(colors));
		m_table.at(Semantic::COLOR).push_back(colorsSpan);
	}

	// Get UV sets 
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
			uvArray[1] = 1-vArray[uIndex];
		}

		const auto uvSpan = reinterpret_span<float>(span(uvSet));
		m_table.at(Semantic::TEXCOORD).push_back(uvSpan);
	}

	// Get tangent sets
	for (auto&& semantic : semantics.descriptions(Semantic::TANGENT))
	{
		MFloatVectorArray mTangents;
		THROW_ON_FAILURE(mesh.getTangents(mTangents, space, &semantic.setName));

		const int numTangents = mTangents.length();

		auto& tangentSet = m_tangentSets[semantic.setIndex];
		tangentSet.reserve(numTangents);

		for (int i = 0; i < numTangents; ++i)
		{
			const auto& t = mTangents[i];
			const auto rht = 2 * mesh.isRightHandedTangent(i, &semantic.setName, &status) - 1.0f;
			THROW_ON_FAILURE(status);
			tangentSet.push_back({t.x, t.y, t.z, rht ? 1.0f : -1.0f});
		}

		const auto tangentSpan = reinterpret_span<float>(span(tangentSet));
		m_table.at(Semantic::TANGENT).push_back(tangentSpan);
	}
}

MeshVertices::~MeshVertices()
{
}

void MeshVertices::dump(IndentableStream& out, const std::string& name) const
{
	dump_vertex_table(out, name, m_table);
}
