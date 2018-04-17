#include "externals.h"
#include "MeshVertices.h"
#include "MayaException.h"
#include "dump.h"
#include "spans.h"
#include "IndentableStream.h"
#include "Arguments.h"
#include "MeshIndices.h"
#include "mikktspace.h"
#include "MeshSkeleton.h"
#include "ExportableScene.h"
#include "ExportableNode.h"

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
	gsl::span<float> tangentComponents;

	MikkTSpaceVectors(const MeshIndices& meshIndices, VertexElementsPerSetIndexTable& vertexTable, const int setIndex)
	{
		const auto numTangents = meshIndices.maxVertexCount();

		// HACK: We assume the indices arrays are large enough here...
		assert(meshIndices.indicesAt(Semantic::TANGENT, setIndex).size() >= numTangents);

		positions = reinterpret_span<Position>(vertexTable.at(Semantic::POSITION).at(0).floats());
		normals = reinterpret_span<Normal>(vertexTable.at(Semantic::NORMAL).at(0).floats());
		texcoords = reinterpret_span<TexCoord>(vertexTable.at(Semantic::TEXCOORD).at(setIndex).floats());
		tangentComponents = mutable_span<float>(vertexTable.at(Semantic::TANGENT).at(setIndex).floats());
	}
};

struct MikkTSpaceContext : SMikkTSpaceContext
{
	const size_t triangleCount;
	const ShapeIndex shapeIndex;
	MikkTSpaceIndices indices;
	MikkTSpaceVectors vectors;
	SMikkTSpaceInterface interface;

	// TODO: It seems MikkTSpace can generate zero tangents for some degenerate triangles, although it does contain code to deal with these.
	// NOTE: Cleaning up the mesh with Maya seems to fix this.
	mutable std::unordered_set<int> invalidTriangleIndices;

	MikkTSpaceContext(
		const MeshIndices& meshIndices,
		VertexElementsPerSetIndexTable& vertexTable,
		const int setIndex,
		const ShapeIndex& shapeIndex)
		: SMikkTSpaceContext{}
		, triangleCount(meshIndices.primitiveCount())
		, shapeIndex(shapeIndex)
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
		const auto count = reinterpret_cast<const MikkTSpaceContext*>(pContext)->triangleCount;
		return static_cast<int>(count);
	}

	static int getNumVerticesOfFace(const SMikkTSpaceContext * pContext, const int iFace)
	{
		return 3;
	}

	static void getPosition(const SMikkTSpaceContext * pContext, float fvPosOut[], const int iFace, const int iVert)
	{
		const auto context = reinterpret_cast<const MikkTSpaceContext*>(pContext);
		const auto index = context->indices.positions[iFace * 3 + iVert];
		const auto& vector = context->vectors.positions[index];
		fvPosOut[0] = vector[0];
		fvPosOut[1] = vector[1];
		fvPosOut[2] = vector[2];
	}

	static void getNormal(const SMikkTSpaceContext* pContext, float fvNormOut[], const int iFace, const int iVert)
	{
		const auto context = reinterpret_cast<const MikkTSpaceContext*>(pContext);
		const auto index = context->indices.normals[iFace * 3 + iVert];
		const auto& vector = context->vectors.normals[index];
		fvNormOut[0] = vector[0];
		fvNormOut[1] = vector[1];
		fvNormOut[2] = vector[2];
	}

	static void getTexCoord(const SMikkTSpaceContext* pContext, float fvTexcOut[], const int iFace, const int iVert)
	{
		const auto context = reinterpret_cast<const MikkTSpaceContext*>(pContext);
		const auto index = context->indices.texcoords[iFace * 3 + iVert];

		if (index < 0)
		{
			fvTexcOut[0] = NAN;
			fvTexcOut[1] = NAN;
		}
		else
		{
			const auto& vector = context->vectors.texcoords[index];
			fvTexcOut[0] = vector[0];
			fvTexcOut[1] = 1 - vector[1];
		}
	}

	static void setTSpaceBasic(const SMikkTSpaceContext* pContext, const float fvTangent[], const float fSign, const int iFace, const int iVert)
	{
		const auto context = reinterpret_cast<const MikkTSpaceContext*>(pContext);

		// Re-index
		const auto index = iFace * 3 + iVert;
		auto& tangentIndexRef = context->indices.tangents[index];

		// If the vertex doesn't have a tangent, don't assign one
		if (tangentIndexRef >= 0)
		{
			tangentIndexRef = index;

			const auto tx = fvTangent[0];
			const auto ty = fvTangent[1];
			const auto tz = fvTangent[2];

			if (tx == 0 && ty == 0 && tz == 0)
			{
				context->invalidTriangleIndices.insert(iFace);
			}

			if (context->shapeIndex.isMainShapeIndex())
			{
				float *p = &context->vectors.tangentComponents[index * array_size<MainShapeTangent>::size];
				p[0] = tx;
				p[1] = ty;
				p[2] = tz;
				p[3] = fSign;
			}
			else
			{
				float *p = &context->vectors.tangentComponents[index * array_size<BlendShapeTangent>::size];
				p[0] = tx;
				p[1] = ty;
				p[2] = tz;
			}
		}
	}
};

MeshVertices::MeshVertices(
	const MeshIndices& meshIndices,
	const MeshSkeleton* meshSkeleton,
	const MFnMesh& mesh,
	ShapeIndex shapeIndex,
	const MPoint& pivotPoint,
	const Arguments& args)
	:shapeIndex(shapeIndex)
{
	MStatus status;

	auto& semantics = meshIndices.semantics;

	// Get points
	MPointArray mPoints;
	THROW_ON_FAILURE(mesh.getPoints(mPoints, MSpace::kTransform));
	const int numPoints = mPoints.length();
	m_positions.reserve(numPoints);

	const auto positionScale = args.scaleFactor;

	for (int i = 0; i < numPoints; ++i)
	{
		const auto p = (mPoints[i] - pivotPoint) * positionScale;
		m_positions.push_back({ static_cast<float>(p.x), static_cast<float>(p.y), static_cast<float>(p.z) });
	}

	const auto positionsSpan = floats(span(m_positions));
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
	THROW_ON_FAILURE(mesh.getNormals(mNormals, MSpace::kWorld));
	const int numNormals = mNormals.length();
	m_normals.reserve(numNormals);
	for (int i = 0; i < numNormals; ++i)
	{
		auto n = mNormals[i];
		m_normals.push_back({ normalSign * n.x, normalSign * n.y, normalSign * n.z });
	}

	const auto normalsSpan = floats(span(m_normals));
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

		const auto colorsSpan = floats(span(colors));
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

		const auto uvSpan = floats(span(uvSet));
		m_table.at(Semantic::TEXCOORD).push_back(uvSpan);
	}

	// Get tangent sets
	for (auto&& semantic : semantics.descriptions(Semantic::TANGENT))
	{
		if (args.mikkelsenTangentAngularThreshold > 0)
		{
			const auto numTriangles = meshIndices.primitiveCount();
			const auto numTangents = numTriangles * 3;

			auto& tangentSet = m_tangentSets[semantic.setIndex];
			tangentSet.resize(numTangents * dimension(Semantic::TANGENT, shapeIndex));

			const auto tangentSpan = floats(span(tangentSet));
			m_table.at(Semantic::TANGENT).push_back(tangentSpan);

			MikkTSpaceContext context(meshIndices, m_table, semantic.setIndex, shapeIndex);
			context.computeTangents(args.mikkelsenTangentAngularThreshold);

			if (!context.invalidTriangleIndices.empty())
			{
				// Don't flood the console output if too many faces are invalid.
				int maxIndices = 10;

				std::stringstream ss;
				ss << "select -r";
				for (auto triangleIndex : context.invalidTriangleIndices)
				{
					ss << ' ' << mesh.name() << ".f[" << meshIndices.triangleToFaceIndex(triangleIndex) << "]";
					if (--maxIndices < 0)
						break;
				}
				ss << ";";

				MayaException::printError(formatted("MikkTSpace generated zero tangents!\nCleanup your mesh and try again please.\nUse the following command select the first invalid faces:\n%s\n\n", ss.str().c_str()));
			}
		}
		else
		{
			MFloatVectorArray mTangents;
			THROW_ON_FAILURE(mesh.getTangents(mTangents, MSpace::kWorld, &semantic.setName));

			const int numTangents = mTangents.length();

			auto& tangentSet = m_tangentSets[semantic.setIndex];
			tangentSet.reserve(numTangents * dimension(Semantic::TANGENT, shapeIndex));

			std::unordered_set<int> invalidTangentIds;

			for (int i = 0; i < numTangents; ++i)
			{
				auto t = mTangents[i];
				const auto rht = 2 * mesh.isRightHandedTangent(i, &semantic.setName, &status) - 1.0f;
				THROW_ON_FAILURE(status);
				tangentSet.push_back(t.x);
				tangentSet.push_back(t.y);
				tangentSet.push_back(t.z);

				auto l = t.x*t.x + t.y*t.y + t.z*t.z;
				if (abs(l - 1) > 1e-6)
				{
					invalidTangentIds.insert(i);
				}

				if (shapeIndex.isMainShapeIndex())
				{
					tangentSet.push_back(rht);
				}
			}

			const auto tangentSpan = floats(span(tangentSet));
			m_table.at(Semantic::TANGENT).push_back(tangentSpan);

			if (!invalidTangentIds.empty())
			{
				auto meshObject = mesh.object(&status);
				THROW_ON_FAILURE(status);

				MItMeshFaceVertex itFaceVertex(meshObject, &status);
				THROW_ON_FAILURE(status);

				// Don't flood the console output if too many vertices are invalid.
				int selectedIndexCount = 0;

				const auto meshName = mesh.name();

				std::stringstream ss;
				ss << formatted("doMenuComponentSelectionExt(\"%s\", \"pvf\", 0);", meshName.asChar()) << endl;
				ss << formatted("setAttr \"%s.displayTangent\" 1;", meshName.asChar()) << endl;
				ss << formatted("checkMeshDisplayNormals \"%s\";", meshName.asChar()) << endl;
				ss << "select -r";

				while (!itFaceVertex.isDone() && selectedIndexCount < 10)
				{
					if (invalidTangentIds.end() != invalidTangentIds.find(itFaceVertex.tangentId()))
					{
						ss << ' ' << mesh.name() << ".vtxFace[" << itFaceVertex.vertId() << "][" << itFaceVertex.faceId() << "]";
						++selectedIndexCount;
					}
					itFaceVertex.next();
				}

				ss << ";";

				// Find the faces with invalid tangents.
				MayaException::printError(formatted("Mesh '%s' has %d invalid tangents!\nAssign texture coordinates and/or cleanup your mesh and try again please.\nUse the following command to visualize the tangents and select the first invalid face-vertices:\n\n%s\n", 
					mesh.name().asChar(), invalidTangentIds.size(), ss.str().c_str()));
			}
		}
	}

	// Get skin joint vertex weights and indices, but only if a skeleton is provided
	if (meshSkeleton)
	{
		// Now group vertex joint assignments into element of multiple components (4 in GLTF)
		const auto vertexJointAssignmentElementSize = int(array_size<JointIndices>::size);

		const auto setCount = int(meshSkeleton->vertexJointAssignmentSetCount());
		const auto& assignmentsTable = meshSkeleton->vertexJointAssignments();

		for (int setIndex = 0; setIndex < setCount; ++setIndex)
		{
			auto& weightsComponents = m_jointWeights[setIndex];
			auto& indicesComponents = m_jointIndices[setIndex];
			weightsComponents.resize(numPoints);
			indicesComponents.resize(numPoints);

			auto weightsSpan = span(weightsComponents);
			auto indicesSpan = span(indicesComponents);

			m_table.at(Semantic::WEIGHTS).push_back(floats(weightsSpan));
			m_table.at(Semantic::JOINTS).push_back(shorts(indicesSpan));

			const auto componentOffset = int(setIndex * vertexJointAssignmentElementSize);

			for (int pointIndex = 0; pointIndex < numPoints; ++pointIndex)
			{
				const auto& assignments = assignmentsTable.at(pointIndex);
				const auto assignmentsSize = int(assignments.size());

				const auto assignmentCount = std::clamp<int>(assignmentsSize - componentOffset, 0, vertexJointAssignmentElementSize);
				const auto assignmentIndex = std::clamp<int>(componentOffset, 0, assignmentsSize - assignmentCount);
				const auto sourceComponents = assignments.subspan(assignmentIndex, assignmentCount);

				const auto targetWeights = mutable_span(reinterpret_span<JointWeight>(weightsSpan.subspan(pointIndex, 1)));
				const auto targetIndices = mutable_span(reinterpret_span<JointIndex>(indicesSpan.subspan(pointIndex, 1)));

				for (auto componentIndex = 0; componentIndex < assignmentCount; ++componentIndex)
				{
					const auto& components = sourceComponents.at(componentIndex);
					targetIndices[componentIndex] = components.jointIndex;
					targetWeights[componentIndex] = components.jointWeight;
				}
			}
		}
	}
}

MeshVertices::~MeshVertices() = default;

void MeshVertices::dump(IndentableStream& out, const std::string& name) const
{
	dump_vertex_table(out, name, m_table, shapeIndex);
}

