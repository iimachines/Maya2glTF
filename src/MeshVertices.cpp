#include "externals.h"
#include "MeshVertices.h"
#include "MayaException.h"
#include "dump.h"
#include "spans.h"
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
	gsl::span<float> tangentComponents;

	MikkTSpaceVectors(const MeshIndices& meshIndices, VertexElementsPerSetIndexTable& vertexTable, const int setIndex)
	{
		const auto numTangents = meshIndices.maxVertexCount();

		// HACK: We assume the indices arrays are large enough here...
		assert(meshIndices.indicesAt(Semantic::TANGENT, setIndex).size() >= numTangents);

		positions = reinterpret_span<Position>(vertexTable.at(Semantic::POSITION).at(0));
		normals = reinterpret_span<Normal>(vertexTable.at(Semantic::NORMAL).at(0));
		texcoords = reinterpret_span<TexCoord>(vertexTable.at(Semantic::TEXCOORD).at(setIndex));
		tangentComponents = mutable_span(vertexTable.at(Semantic::TANGENT).at(setIndex));
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
	mutable std::vector<int> invalidTriangleIndices;

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
		const auto& vector = context->vectors.texcoords[index];
		fvTexcOut[0] = vector[0];
		fvTexcOut[1] = 1 - vector[1];
	}

	static void setTSpaceBasic(const SMikkTSpaceContext* pContext, const float fvTangent[], const float fSign, const int iFace, const int iVert)
	{
		const auto context = reinterpret_cast<const MikkTSpaceContext*>(pContext);

		// Re-index
		const auto index = iFace * 3 + iVert;
		context->indices.tangents[index] = index;

		const auto tx = fvTangent[0];
		const auto ty = fvTangent[1];
		const auto tz = fvTangent[2];

		if (tx == 0 && ty == 0 && tz == 0)
		{
			context->invalidTriangleIndices.push_back(iFace);
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
};

MeshVertices::MeshVertices(
	const MeshIndices& meshIndices,
	const MFnMesh& mesh,
	ShapeIndex shapeIndex,
	const Arguments& args,
	MSpace::Space space)
	:shapeIndex(shapeIndex)
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
			tangentSet.resize(numTangents * dimension(Semantic::TANGENT, shapeIndex));

			const auto tangentSpan = span(tangentSet);
			m_table.at(Semantic::TANGENT).push_back(tangentSpan);

			MikkTSpaceContext context(meshIndices, m_table, semantic.setIndex, shapeIndex);
			context.computeTangents(args.mikkelsenTangentAngularThreshold);

			if (!context.invalidTriangleIndices.empty())
			{
				// Don't flood the console output if too many faces are invalid.
				if (context.invalidTriangleIndices.size() > 10)
					context.invalidTriangleIndices.resize(10);

				std::stringstream ss;
				ss << "select -r";
				for (auto triangleIndex : context.invalidTriangleIndices)
				{
					ss << ' ' << mesh.name() << ".f[" << meshIndices.triangleToFaceIndex(triangleIndex) << "]";
				}
				ss << ";";

				MayaException::printError(formatted("MikkTSpace generated zero tangents!\nCleanup your mesh and try again please.\nUse the following command select the first invalid faces:\n%s\n", ss.str().c_str()));
			}
		}
		else
		{
			const int numTangents = mTangents.length();

			auto& tangentSet = m_tangentSets[semantic.setIndex];
			tangentSet.reserve(numTangents * dimension(Semantic::TANGENT, shapeIndex));

			for (int i = 0; i < numTangents; ++i)
			{
				const auto& t = mTangents[i];
				const auto rht = 2 * mesh.isRightHandedTangent(i, &semantic.setName, &status) - 1.0f;
				THROW_ON_FAILURE(status);
				tangentSet.push_back(t.x);
				tangentSet.push_back(t.y);
				tangentSet.push_back(t.z);

				if (shapeIndex.isMainShapeIndex())
				{
					tangentSet.push_back(rht);
				}
			}

			const auto tangentSpan = span(tangentSet);
			m_table.at(Semantic::TANGENT).push_back(tangentSpan);
		}
	}

	// Get skin joint vertex weights and indices, but only for the main mesh
	// Although Maya does allow skinning to be applied to blend-shapes, we don't support that.
	if (shapeIndex.isMainShapeIndex())
	{
		MObject skin = tryExtractSkinCluster(mesh, args.ignoreMeshDeformers);
		MFnSkinCluster fnSkin(skin, &status);
		if (status)
		{
			// Gather all the joints
			MDagPathArray jointDagPaths;
			const auto jointCount = fnSkin.influenceObjects(jointDagPaths, &status);
			THROW_ON_FAILURE(status);

			m_joints.reserve(jointCount);

			for (size_t index = 0; index < jointCount; ++index)
			{
				auto& jointDagPath = jointDagPaths[static_cast<unsigned int>(index)];

				const auto matrix = jointDagPath.inclusiveMatrixInverse(&status);
				THROW_ON_FAILURE(status);

				m_joints.emplace_back(jointDagPath, matrix);
			}

			// Gather all joint index/weights per vertex, sorted ascendingly by weight
			const auto meshDagPath = mesh.dagPath(&status);
			THROW_ON_FAILURE(status);

			MItGeometry iterGeom(meshDagPath, &status);
			THROW_ON_FAILURE(status);

			assert(iterGeom.count() == m_positions.size());

			MFloatArray vertexWeights;
			unsigned int numWeights;

			// Build joint (index,weight) pair groups, per vertex
			std::vector<std::pair<unsigned int, float>> weightIndexPairs;
			std::vector<int> pairsIndexPerVertex;
			std::vector<int> pairsCountPerVertex;

			pairsIndexPerVertex.resize(numPoints);
			pairsCountPerVertex.resize(numPoints);

			weightIndexPairs.reserve(8 * numPoints);

			int maxPairsCount = 0;

			for (; !iterGeom.isDone(); iterGeom.next())
			{
				const auto pointIndex = iterGeom.index(&status);
				THROW_ON_FAILURE(status);

				const MObject component = iterGeom.component(&status);
				THROW_ON_FAILURE(status);

				status = fnSkin.getWeights(meshDagPath, component, vertexWeights, numWeights);
				THROW_ON_FAILURE(status);

				const auto pairsIndex = pairsIndexPerVertex[pointIndex] = int(weightIndexPairs.size());

				for (unsigned int jointIndex = 0; jointIndex < numWeights; ++jointIndex)
				{
					const float jointWeight = vertexWeights[jointIndex];
					if (std::abs(jointWeight) > 1e-6f)
					{
						weightIndexPairs.emplace_back(jointIndex, jointWeight);
					}
				}

				int pairsCount = pairsCountPerVertex[pointIndex] = int(weightIndexPairs.size()) - pairsIndex;

				maxPairsCount = std::max(pairsCount, maxPairsCount);

				// Sort weights from large to small.
				// TODO: Use insertion sort when adding the weights?
				const auto itPairsBgn = weightIndexPairs.begin() + pairsIndex;
				const auto itPairsEnd = itPairsBgn + pairsCount;
				std::sort(itPairsBgn, itPairsEnd, [](auto &left, auto &right) {
					return left.second > right.second;
				});
			}

			std::cout << prefix << "Skin for mesh " << meshDagPath.partialPathName().asChar() << " will use " << maxPairsCount << " weights per vertex" << endl;

			// Now group weights and indices into 4-aligned packets.
			// HACK: Each packet will become a 'set-index' (should be renamed).
			// This conventienly works out in the vertex-welder
			const auto packetSize = 4;
			const auto setCount = (maxPairsCount + packetSize - 1) / packetSize;

			for (int setIndex = 0; setIndex < setCount; ++setIndex)
			{
				auto& weightsPackets = m_jointWeights[setIndex];
				auto& indicesPackets = m_jointIndices[setIndex];
				weightsPackets.resize(numPoints);
				indicesPackets.resize(numPoints);

				auto weightsSpan = span(weightsPackets);
				auto indicesSpan = span(indicesPackets);
				auto pairsSpan = span(weightIndexPairs);

				const auto packetOffset = setIndex * packetSize;

				for (int pointIndex = 0; pointIndex < numPoints; ++pointIndex)
				{
					const auto pairsIndex = pairsIndexPerVertex.at(pointIndex) + packetOffset;
					const auto pairsCount = std::clamp(pairsCountPerVertex.at(pointIndex) - packetOffset, 0, packetSize);
					const auto sourcePairs = pairsSpan.subspan(pairsIndex, pairsCount);

					const auto targetWeights = mutable_span(reinterpret_span<float>(weightsSpan.subspan(pointIndex, 1)));
					const auto targetIndices = mutable_span(reinterpret_span<float>(indicesSpan.subspan(pointIndex, 1)));

					for (int componentIndex=0; componentIndex<pairsCount; ++componentIndex)
					{
						const auto& pair = sourcePairs.at(componentIndex);
						targetIndices[componentIndex] = pair.first;
						targetWeights[componentIndex] = pair.second;
					}
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

MObject MeshVertices::tryExtractSkinCluster(const MFnMesh& fnMesh, const MSelectionList& ignoredDeformers)
{
	MObject cluster;

	// Iterate upstream to find all the nodes that affect the mesh.
	MStatus status;
	MPlug plug = fnMesh.findPlug("inMesh", status);
	THROW_ON_FAILURE(status);

	if (plug.isConnected())
	{
		MItDependencyGraph dgIt(plug,
			MFn::kInvalid,
			MItDependencyGraph::kUpstream,
			MItDependencyGraph::kBreadthFirst,
			MItDependencyGraph::kNodeLevel,
			&status);

		THROW_ON_FAILURE(status);

		dgIt.disablePruningOnFilter();

		for (; !dgIt.isDone(); dgIt.next())
		{
			MObject thisNode = dgIt.thisNode();
			if (thisNode.hasFn(MFn::kSkinClusterFilter))
			{
				MFnSkinCluster fnSkinCluster(thisNode, &status);

				const auto thisName = MFnDependencyNode(thisNode).name();

				if (status == MStatus::kSuccess)
				{
					if (ignoredDeformers.hasItem(thisNode))
					{
						cout << prefix << "ignoring skin cluster" << thisName << endl;
					}
					else if (cluster.isNull())
					{
						cluster = thisNode;
					}
					else
					{
						cerr << prefix << "only a single skin cluster is supported, skipping " << thisName << endl;
					}
				}
				else
				{
					cerr << prefix << "unable to extract skin cluster from " << thisName << ", reason: " << status.error() << endl;
				}
			}
		}
	}

	return cluster;
}