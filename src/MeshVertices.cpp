#include "externals.h"
#include "MeshVertices.h"
#include "MayaException.h"
#include "dump.h"
#include "Spans.h"
#include "DagHelper.h"
#include "IndentableStream.h"
#include "Arguments.h"
#include "MeshIndices.h"
#include "mikktspace.h"

struct MikkTSpaceIndices
{
	gsl::span<const Index> positions;
	gsl::span<const Index> normals;
	gsl::span<const Index> texcoords;
	gsl::span<Index> tangents;

	MikkTSpaceIndices(const MeshIndices& meshIndices, const int setIndex)
	{
		positions = gsl::make_span(meshIndices.indicesAt(Semantic::POSITION, 0));
		normals = gsl::make_span(meshIndices.indicesAt(Semantic::NORMAL, 0));
		texcoords = gsl::make_span(meshIndices.indicesAt(Semantic::TEXCOORD, setIndex));
		tangents = mutable_span(gsl::make_span(meshIndices.indicesAt(Semantic::TANGENT, setIndex)));
	}
};

struct MikkTSpaceVectors
{
	gsl::span<const Position> positions;
	gsl::span<const Normal> normals;
	gsl::span<const TexCoord> texcoords;
	gsl::span<Tangent> tangents;

	MikkTSpaceVectors(const MeshIndices& meshIndices, VertexElementsPerSetIndexTable& vertexTable, const int setIndex)
	{
		const auto numTangents = meshIndices.maxVertexCount();

		// HACK: We assume the indices arrays are large enough here...
		assert(meshIndices.indicesAt(Semantic::TANGENT, setIndex).size() >= numTangents);

		positions = reinterpret_span<Position>(vertexTable.at(Semantic::POSITION).at(0));
		normals = reinterpret_span<Normal>(vertexTable.at(Semantic::NORMAL).at(0));
		texcoords = reinterpret_span<TexCoord>(vertexTable.at(Semantic::TEXCOORD).at(setIndex));
		tangents = mutable_span(reinterpret_span<Tangent>(vertexTable.at(Semantic::TANGENT).at(setIndex)));
	}
};

struct MikkTSpaceContext : SMikkTSpaceContext
{
	const size_t triangleCount;
	MikkTSpaceIndices indices;
	MikkTSpaceVectors vectors;
	SMikkTSpaceInterface interface;

	MikkTSpaceContext(
		const MeshIndices& meshIndices,
		VertexElementsPerSetIndexTable& vertexTable,
		const int setIndex)
		: triangleCount(meshIndices.primitiveCount())
		, indices(meshIndices, setIndex)
		, vectors(meshIndices, vertexTable, setIndex)
		, interface {}
	{
		m_pInterface = &interface;
		m_pUserData = this;

		interface.m_getNumFaces = getNumFaces;
		interface.m_getNumVerticesOfFace = getNumVerticesOfFace;
		interface.m_getPosition = getPosition;
		interface.m_getNormal = getNormal;
		interface.m_getTexCoord = getTexCoord;
		interface.m_setTSpaceBasic = setTSpaceBasic;
	}

	void computeTangents(const double angularThreshold) const
	{
		const auto mkr = genTangSpace(this, static_cast<float>(angularThreshold));

		if (!mkr)
		{
			MayaException::printError("Failed to get Mikkelsen tangents (aka MikkTSpace)");
		}
	}

	static int getNumFaces(const SMikkTSpaceContext * pContext)
	{
		auto count = static_cast<const MikkTSpaceContext*>(pContext)->triangleCount;
		return static_cast<int>(count);
	}

	static int getNumVerticesOfFace(const SMikkTSpaceContext * pContext, const int iFace)
	{
		return 3;
	}

	static void getPosition(const SMikkTSpaceContext * pContext, float fvPosOut[], const int iFace, const int iVert)
	{
		const auto context = static_cast<const MikkTSpaceContext*>(pContext);
		const auto index = context->indices.positions[iFace * 3 + iVert];
		const auto& vector = context->vectors.positions[index];
		fvPosOut[0] = vector[0];
		fvPosOut[1] = vector[1];
		fvPosOut[2] = vector[2];
	}

	static void getNormal(const SMikkTSpaceContext* pContext, float fvNormOut[], const int iFace, const int iVert)
	{
		const auto context = static_cast<const MikkTSpaceContext*>(pContext);
		const auto index = context->indices.normals[iFace * 3 + iVert];
		const auto& vector = context->vectors.normals[index];
		fvNormOut[0] = vector[0];
		fvNormOut[1] = vector[1];
		fvNormOut[2] = vector[2];
	}
	static void getTexCoord(const SMikkTSpaceContext* pContext, float fvTexcOut[], const int iFace, const int iVert)
	{
		const auto context = static_cast<const MikkTSpaceContext*>(pContext);
		const auto index = context->indices.texcoords[iFace * 3 + iVert];
		const auto& vector = context->vectors.texcoords[index];
		fvTexcOut[0] = vector[0];
		fvTexcOut[1] = vector[1];
	}

	static void setTSpaceBasic(const SMikkTSpaceContext* pContext, const float fvTangent[], const float fSign, const int iFace, const int iVert)
	{
		const auto context = static_cast<const MikkTSpaceContext*>(pContext);
		// Re-index
		const auto index = iFace * 3 + iVert;
		context->indices.tangents[index] = index;
		context->vectors.tangents[index] = { fvTangent[0],fvTangent[1],fvTangent[2],fSign };
	}
};



MeshVertices::MeshVertices(const MeshIndices& meshIndices, const MFnMesh& mesh, const Arguments& args, MSpace::Space space)
{
	MStatus status;

	auto& semantics = meshIndices.semantics;

	// Get points
	MPointArray mPoints;
	THROW_ON_FAILURE(mesh.getPoints(mPoints, space));
	const int numPoints = mPoints.length();
	m_positions.reserve(numPoints);

	const auto positionScale = args.scaleFactor;

	for (int i = 0; i < numPoints; ++i)
	{
		const auto p = mPoints[i] * positionScale;
		m_positions.push_back({ static_cast<float>(p.x), static_cast<float>(p.y), static_cast<float>(p.z) });
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
		m_normals.push_back({ normalSign * n.x, normalSign * n.y, normalSign * n.z });
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
			colors.push_back({ c.r, c.g, c.b, c.a });
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
			uvArray[1] = 1 - vArray[uIndex];
		}

		const auto uvSpan = reinterpret_span<float>(span(uvSet));
		m_table.at(Semantic::TEXCOORD).push_back(uvSpan);
	}

	// Get tangent sets
	for (auto&& semantic : semantics.descriptions(Semantic::TANGENT))
	{
		MFloatVectorArray mTangents;
		THROW_ON_FAILURE(mesh.getTangents(mTangents, space, &semantic.setName));

		if (args.mikkelsenTangentAngularThreshold > 0)
		{
			const auto numTriangles = meshIndices.primitiveCount();
			const auto numTangents = numTriangles * 3;

			auto& tangentSet = m_tangentSets[semantic.setIndex];
			tangentSet.resize(numTangents);

			const auto tangentSpan = reinterpret_span<float>(span(tangentSet));
			m_table.at(Semantic::TANGENT).push_back(tangentSpan);

			MikkTSpaceContext context(meshIndices, m_table, semantic.setIndex);
			context.computeTangents(args.mikkelsenTangentAngularThreshold);
		}
		else
		{
			const int numTangents = mTangents.length();

			auto& tangentSet = m_tangentSets[semantic.setIndex];
			tangentSet.reserve(numTangents);

			for (int i = 0; i < numTangents; ++i)
			{
				const auto& t = mTangents[i];
				const auto rht = 2 * mesh.isRightHandedTangent(i, &semantic.setName, &status) - 1.0f;
				THROW_ON_FAILURE(status);
				tangentSet.push_back({ t.x, t.y, t.z, rht });
			}

			const auto tangentSpan = reinterpret_span<float>(span(tangentSet));
			m_table.at(Semantic::TANGENT).push_back(tangentSpan);
		}
	}
}

MeshVertices::~MeshVertices()
{
}

void MeshVertices::dump(IndentableStream& out, const std::string& name) const
{
	dump_vertex_table(out, name, m_table);
}
