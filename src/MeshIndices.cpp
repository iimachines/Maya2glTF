#include "externals.h"
#include "MeshIndices.h"
#include "MayaException.h"
#include "spans.h"
#include "dump.h"

MeshIndices::MeshIndices(const MeshSemantics& semantics, const MFnMesh& fnMesh)
	:meshName(fnMesh.partialPathName().asChar())
{
	MStatus status;

	const auto instanceCount = fnMesh.instanceCount(false);

	std::vector<MIntArray> mapPolygonToShaderPerInstance(instanceCount);

	const auto numPolygons = fnMesh.numPolygons();

	for (unsigned instanceIndex=0; instanceIndex<instanceCount; ++instanceIndex)
	{
		auto& shading = m_shadingPerInstance[instanceIndex];
		THROW_ON_FAILURE(fnMesh.getConnectedShaders(instanceIndex, shading.shaderGroups, mapPolygonToShaderPerInstance[instanceIndex]));
		shading.primitiveToShaderIndexMap.reserve(numPolygons * 2);
	}


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
	auto& tangentSets = m_table.at(Semantic::TANGENT);
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
			for (unsigned instanceIndex = 0; instanceIndex<instanceCount; ++instanceIndex)
			{
				auto& shading = m_shadingPerInstance[instanceIndex];
				const auto shaderIndex = mapPolygonToShaderPerInstance.at(instanceIndex)[polygonIndex];
				shading.primitiveToShaderIndexMap.push_back(shaderIndex);
			}

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
						// This polygon has no associated colors.
						colorSets.at(setIndex).push_back(NoIndex);
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

						// TODO: Not sure why Maya doesn't allow use to pass the uvSetName here?
						// Maybe a polygon vertex can only have a single tangent assigned to it?
						const auto tangentIndex = itPoly.tangentIndex(localVertexIndex, &status);
						THROW_ON_FAILURE(status);
						tangentSets.at(setIndex).push_back(tangentIndex);
					}
					else
					{
						uvSets.at(setIndex).push_back(NoIndex);
						tangentSets.at(setIndex).push_back(NoIndex);
					}
				}
			}
		}
	}
}

MeshIndices::~MeshIndices()
{
}

void MeshIndices::dump(std::ostream& out, const std::string& name, const std::string& indent) const
{
	dump_table(out, name, m_table, indent);
}


