#include "externals.h"
#include "MeshIndices.h"
#include "MayaException.h"
#include "Spans.h"

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
	for (auto i = 0; i<Semantic::COUNT; ++i)
	{
		m_indices[i].reserve(numPolygons * 6);
	}

	m_primitiveToShaderIndexMap.reserve(numPolygons * 2);

	auto& positions = m_indices[Semantic::POSITION];
	auto& normals = m_indices[Semantic::NORMAL];
	auto& tangents = m_indices[Semantic::TANGENT];
	auto& texCoords = m_indices[Semantic::TEXCOORD];
	auto& colors = m_indices[Semantic::COLOR];

	auto polygonIndex = 0;
	for (MItMeshPolygon itPoly(fnMesh.object()); !itPoly.isDone(); itPoly.next(), ++polygonIndex)
	{
		auto numTrianglesInPolygon = 0;
		status = itPoly.numTriangles(numTrianglesInPolygon);
		THROW_ON_FAILURE(status);

		const auto hasUVs = itPoly.hasUVs();

		// NOTE: This can be negative when no shader is attached (e.g. blend shapes)
		int shaderIndex = mapPolygonToShader[polygonIndex];
		if (shaderIndex >= 0)
		{
			m_isShaderUsed[shaderIndex] = true;
		}

		for (int localTriangleIndex = 0; localTriangleIndex < numTrianglesInPolygon; ++localTriangleIndex)
		{
			m_primitiveToShaderIndexMap.push_back(shaderIndex);

			// TODO: Use Maya's triangulation here, and figure out how to look up the normal properly
			for (int i = 0; i<3; ++i)
			{
				int localVertexIndex = i == 0 ? 0 : i + localTriangleIndex;

				int positionIndex = itPoly.vertexIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				positions.push_back(positionIndex);

				int normalIndex = itPoly.normalIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				normals.push_back(normalIndex);

				int tangentIndex = itPoly.tangentIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				tangents.push_back(tangentIndex);

				int colorIndex;
				status = itPoly.getColorIndex(localVertexIndex, colorIndex);
				THROW_ON_FAILURE(status);
				colors.push_back(colorIndex);

				// TODO: We assume either all or no triangles should have texture coordinates...
				// TODO: Support multiple UV-sets
				int texCoordIndex = 0;
				if (hasUVs)
				{
					THROW_ON_FAILURE(itPoly.getUVIndex(localVertexIndex, texCoordIndex));
				}
				texCoords.push_back(texCoordIndex);
			}
		}
	}
}

MeshIndices::~MeshIndices()
{
}

void MeshIndices::dump(const std::string name, const std::string indent) const
{
	auto& positions = m_indices[Semantic::POSITION];
	auto& normals = m_indices[Semantic::NORMAL];
	auto& tangents = m_indices[Semantic::TANGENT];
	auto& texCoords = m_indices[Semantic::TEXCOORD];
	auto& colors = m_indices[Semantic::COLOR];

	cout << indent << name << ": {" << endl;
	const auto subIndent = indent + "\t";
	dump_span<float>("POSITION", span(positions), subIndent);
	cout << subIndent << "," << endl;
	dump_span<float>("NORMAL", span(normals), subIndent);
	cout << subIndent << "," << endl;
	dump_span<float>("TEXCOORD", span(texCoords), subIndent);
	cout << subIndent << "," << endl;
	dump_span<float>("TANGENT", span(tangents), subIndent);
	cout << subIndent << "," << endl;
	dump_span<float>("COLOR", span(colors), subIndent);
	cout << "}" << endl;
}

