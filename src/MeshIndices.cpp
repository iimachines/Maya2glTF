#include "externals.h"
#include "MeshIndices.h"
#include "MayaException.h"
#include "spans.h"
#include "dump.h"

MeshIndices::MeshIndices(const MeshSemantics& semantics, const MFnMesh& fnMesh)
{
	MStatus status;
	MIntArray mapPolygonToShader;

	// TODO: Deal with instances?
	const auto instanceNumber = 0;
	THROW_ON_FAILURE(fnMesh.getConnectedShaders(instanceNumber, m_shaders, mapPolygonToShader));

	const auto shaderCount = m_shaders.length();
	m_isShaderUsed.resize(shaderCount, false);

	const auto numPolygons = fnMesh.numPolygons();

	m_primitiveToShaderIndexMap.reserve(numPolygons * 2);

	// Reserve space for the indices, we assume every polygon is a quad.
	for (auto kind = 0; kind<Semantic::COUNT; ++kind)
	{
		auto& indexSet = m_table.at(kind);
		const auto n = semantics.descriptions(Semantic::from(kind)).size();
		for (auto set = 0; set<n; ++set)
		{
			IndexVector indices;
			indices.reserve(numPolygons * 6);
			indexSet.push_back(indices);
		}
	}

	auto& positions = m_table.at(Semantic::POSITION).at(0);
	auto& normals = m_table.at(Semantic::NORMAL).at(0);
	auto& uvSets = m_table.at(Semantic::TEXCOORD);
	auto& colorSets = m_table.at(Semantic::COLOR);

	auto& colorSemantics = semantics.descriptions(Semantic::COLOR);
	auto& uvSetSemantics = semantics.descriptions(Semantic::TEXCOORD);

	const auto colorSetCount = colorSemantics.size();
	const auto uvSetCount = uvSetSemantics.size();


	const auto numVertices = fnMesh.numVertices(&status);
	THROW_ON_FAILURE(status);

	std::vector<int> localPolygonVertices(numVertices);

	MPointArray triangleVertexPoints;
	MIntArray triangleVertexIndices;
	MIntArray polygonVertexIndices;

	for (MItMeshPolygon itPoly(fnMesh.object()); !itPoly.isDone(); itPoly.next())
	{
		const auto polygonIndex = itPoly.index(&status);
		THROW_ON_FAILURE(status);

		auto numTrianglesInPolygon = 0;
		THROW_ON_FAILURE(itPoly.numTriangles(numTrianglesInPolygon));

		// NOTE: This can be negative when no shader is attached (e.g. blend shapes)
		int shaderIndex = mapPolygonToShader[polygonIndex];
		if (shaderIndex >= 0)
		{
			m_isShaderUsed[shaderIndex] = true;
		}

		// Map mesh-vertex-indices to face-vertex-indices.
		// TODO: Figure out what Maya API does this for us;
		// we just need the triangles using face-vertex-indices
		THROW_ON_FAILURE(itPoly.getVertices(polygonVertexIndices));
		const int numPolygonVertices = polygonVertexIndices.length();
		for (auto polygonVertexIndex = 0; polygonVertexIndex<numPolygonVertices; ++polygonVertexIndex)
		{
			const auto meshVertexIndex = polygonVertexIndices[polygonVertexIndex];
			localPolygonVertices[meshVertexIndex] = polygonVertexIndex;
		}

		THROW_ON_FAILURE(itPoly.getTriangles(triangleVertexPoints, triangleVertexIndices));

		const auto numLocalVertices = numTrianglesInPolygon * 3;
		assert(triangleVertexPoints.length() == numLocalVertices);
		assert(triangleVertexIndices.length() == numLocalVertices);

		int triangleVertexIndex = 0;

		for (auto localTriangleIndex = 0; localTriangleIndex < numTrianglesInPolygon; ++localTriangleIndex)
		{
			m_primitiveToShaderIndexMap.push_back(shaderIndex);

			for (auto i = 0; i<3; ++i, ++triangleVertexIndex)
			{
				const auto meshVertexIndex = triangleVertexIndices[triangleVertexIndex];
				const auto localVertexIndex = localPolygonVertices[meshVertexIndex];

				int positionIndex = itPoly.vertexIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				positions.push_back(positionIndex);

				int normalIndex = itPoly.normalIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				normals.push_back(normalIndex);

				for (auto setIndex=0; setIndex<colorSetCount; ++setIndex)
				{
					int colorIndex;
					auto& colorSetName = colorSemantics[setIndex].setName;

					if (itPoly.hasColor(localVertexIndex))
					{
						status = itPoly.getColorIndex(localVertexIndex, colorIndex, &colorSetName);
						THROW_ON_FAILURE(status);
						colorSets.at(setIndex).push_back(colorIndex);
					}
					else
					{
						// TODO: This polygon has no associated colors, but the mesh has. What should we do here?
						colorSets.at(setIndex).push_back(0);
					}
				}

				for (auto setIndex = 0; setIndex<uvSetCount; ++setIndex)
				{
					int uvIndex;
					auto& uvSetName = uvSetSemantics[setIndex].setName;
					if (itPoly.hasUVs(uvSetName))
					{
						status = itPoly.getUVIndex(localVertexIndex, uvIndex, &uvSetName);
						THROW_ON_FAILURE(status);
						uvSets.at(setIndex).push_back(uvIndex);
					}
					else
					{
						// TODO: This polygon has no associated UVs, but the mesh has. What should we do here?
						uvSets.at(setIndex).push_back(0);
					}
				}
			}
		}
	}
}

MeshIndices::~MeshIndices()
{
}

void MeshIndices::dump(const std::string& name, const std::string& indent) const
{
	dump_table(name, m_table, indent);
}


