#include "externals.h"
#include "MeshIndices.h"
#include "MayaException.h"
#include "spans.h"
#include "dump.h"

MeshIndices::MeshIndices(const MeshSetNames& setNames, const MFnMesh& fnMesh)
{
	MStatus status;
	MObjectArray shaders;
	MIntArray mapPolygonToShader;

	// TODO: Deal with instances?
	const auto instanceNumber = 0;
	THROW_ON_FAILURE(fnMesh.getConnectedShaders(instanceNumber, shaders, mapPolygonToShader));

	const auto shaderCount = shaders.length();
	m_isShaderUsed.resize(shaderCount, false);

	const auto numPolygons = fnMesh.numPolygons();

	m_primitiveToShaderIndexMap.reserve(numPolygons * 2);

	// Reserve space for the indices, we assume every polygon is a quad.
	for (auto semantic = 0; semantic<Semantic::COUNT; ++semantic)
	{
		auto indexSet = m_indexSets.at(semantic);
		const auto n = setNames.numSetsOf(Semantic::from(semantic));
		for (auto set = 0; set<n; ++set)
		{
			indexSet[set].reserve(numPolygons * 6);
		}
	}

	auto& positions = m_indexSets.at(Semantic::POSITION).at(0);
	auto& normals = m_indexSets.at(Semantic::NORMAL).at(0);
	auto& uvSets = m_indexSets.at(Semantic::TEXCOORD);
	auto& colorSets = m_indexSets.at(Semantic::COLOR);

	auto& colorSetNames = setNames.colors();
	auto& uvSetNames = setNames.texCoords();

	const int colorSetCount = colorSetNames.length();
	const int uvSetCount = uvSetNames.length();

	auto polygonIndex = 0;
	for (MItMeshPolygon itPoly(fnMesh.object()); !itPoly.isDone(); itPoly.next(), ++polygonIndex)
	{
		auto numTrianglesInPolygon = 0;
		THROW_ON_FAILURE(itPoly.numTriangles(numTrianglesInPolygon));

		// NOTE: This can be negative when no shader is attached (e.g. blend shapes)
		int shaderIndex = mapPolygonToShader[polygonIndex];
		if (shaderIndex >= 0)
		{
			m_isShaderUsed[shaderIndex] = true;
		}

		for (auto localTriangleIndex = 0; localTriangleIndex < numTrianglesInPolygon; ++localTriangleIndex)
		{
			m_primitiveToShaderIndexMap.push_back(shaderIndex);

			// TODO: Use Maya's triangulation here, and figure out how to look up the normal properly
			for (auto i = 0; i<3; ++i)
			{
				const auto localVertexIndex = i == 0 ? 0 : i + localTriangleIndex;

				int positionIndex = itPoly.vertexIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				positions.push_back(positionIndex);

				int normalIndex = itPoly.normalIndex(localVertexIndex, &status);
				THROW_ON_FAILURE(status);
				normals.push_back(normalIndex);

				for (auto setIndex=0; setIndex<colorSetCount; ++setIndex)
				{
					int colorIndex;
					auto colorSetName = colorSetNames[setIndex];
					status = itPoly.getColorIndex(localVertexIndex, colorIndex, &colorSetName);
					THROW_ON_FAILURE(status);
					colorSets.at(setIndex).push_back(colorIndex);
				}

				for (auto setIndex = 0; setIndex<uvSetCount; ++setIndex)
				{
					int uvIndex;
					auto uvSetName = uvSetNames[setIndex];
					status = itPoly.getUVIndex(localVertexIndex, uvIndex, &uvSetName);
					THROW_ON_FAILURE(status);
					uvSets.at(setIndex).push_back(uvIndex);
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
	auto& positions = m_indexSets[Semantic::POSITION].at(0);
	auto& normals = m_indexSets[Semantic::NORMAL].at(0);
	auto& uvSets = m_indexSets[Semantic::TEXCOORD];
	auto& colorSets = m_indexSets[Semantic::COLOR];

	cout << indent << name << ": {" << endl;
	const auto subIndent = indent + "\t";
	
	dump_span<float>("POSITION", span(positions), subIndent);
	cout << subIndent << "," << endl;
	
	dump_span<float>("NORMAL", span(normals), subIndent);
	cout << subIndent << "," << endl;
	
	for (const auto pair : uvSets)
		dump_span<float>("TEXCOORD_" + pair.first, span(pair.second), subIndent);

	if (!uvSets.empty())
		cout << subIndent << "," << endl;

	for (const auto pair : colorSets)
		dump_span<float>("COLOR_" + pair.first, span(pair.second), subIndent);

	if (!colorSets.empty())
		cout << endl;

	cout << indent << "}" << endl;
}

