#include "externals.h"
#include "MeshIndices.h"
#include "MayaException.h"

MeshIndices::MeshIndices(MFnMesh fnMesh)
{
	MStatus status;
	MObjectArray shaders;
	MIntArray mapPolygonToShader;
	status = fnMesh.getConnectedShaders(0, shaders, mapPolygonToShader);
	THROW_ON_FAILURE(status);

	const auto shaderCount = shaders.length();

	m_isShaderUsed.resize(shaderCount, false);

	const auto numPolygons = fnMesh.numPolygons();

	// Reserve space for the indices, we assume every polygon is a quad.
	for (auto i = 0; i<NUM_SEMANTICS; ++i)
	{
		m_indices[i].reserve(numPolygons * 6);
	}

	m_primitiveToShaderIndexMap.reserve(numPolygons * 2);

	auto polygonIndex = 0;
	for (MItMeshPolygon itPoly(fnMesh.object()); !itPoly.isDone(); itPoly.next(), ++polygonIndex)
	{
		auto numTrianglesInPolygon = 0;
		status = itPoly.numTriangles(numTrianglesInPolygon);
		THROW_ON_FAILURE(status);

		const auto hasUVs = itPoly.hasUVs();

		// NOTE: This can be negative when no shader is attached (e.g. blend shapes)
		int shaderIndex = mapPolygonToShader[polygonIndex];
		m_isShaderUsed[shaderIndex] = shaderIndex != -1;

		for (int localTriangleIndex = 0; localTriangleIndex < numTrianglesInPolygon; ++localTriangleIndex)
		{
			m_primitiveToShaderIndexMap.push_back(shaderIndex);

			// TODO: Use Maya's triangulation here, and figure out how to look up the normal properly
			for (int i = 0; i<3; ++i)
			{
				int localVertexIndex = i == 0 ? 0 : i + localTriangleIndex;

				int positionIndex = itPoly.vertexIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				m_indices[POSITION].push_back(positionIndex);

				int normalIndex = itPoly.normalIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				m_indices[NORMAL].push_back(normalIndex);

				int tangentIndex = itPoly.tangentIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				m_indices[TANGENT].push_back(tangentIndex);

				// TODO: We assume either all or no triangles should have texture coordinates...
				// TODO: Support multiple UV-sets
				int texCoordIndex = 0;
				if (hasUVs)
				{
					THROW_ON_FAILURE(itPoly.getUVIndex(localVertexIndex, texCoordIndex));
				}
				m_indices[TEXCOORD].push_back(texCoordIndex);
			}
		}
	}
}


MeshIndices::~MeshIndices()
{
}
