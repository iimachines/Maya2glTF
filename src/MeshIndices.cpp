#include "MeshIndices.h"
#include "MayaException.h"
#include "dump.h"
#include "externals.h"

MeshIndices::MeshIndices(const MeshSemantics *meshSemantics,
                         const MFnMesh &fnMesh)
    : meshName(fnMesh.partialPathName().asChar()), semantics(*meshSemantics) {
    MStatus status;

    const auto instanceCount = fnMesh.instanceCount(true);

    std::vector<MIntArray> mapPolygonToShaderPerInstance(instanceCount);

    const auto numPolygons = fnMesh.numPolygons();

    for (unsigned instanceIndex = 0; instanceIndex < instanceCount;
         ++instanceIndex) {
        auto &shading = m_shadingPerInstance[instanceIndex];
        THROW_ON_FAILURE(fnMesh.getConnectedShaders(
            instanceIndex, shading.shaderGroups,
            mapPolygonToShaderPerInstance[instanceIndex]));
        shading.primitiveToShaderIndexMap.reserve(numPolygons * 2);
    }

    m_TriangleCount = 0;
    for (MItMeshPolygon itPoly(fnMesh.object()); !itPoly.isDone();
         itPoly.next()) {
        int triangleCount;
        THROW_ON_FAILURE(itPoly.numTriangles(triangleCount));
        m_TriangleCount += triangleCount;
    }

    for (auto kind = 0; kind < Semantic::COUNT; ++kind) {
        auto &indexSet = m_table.at(kind);
        const auto n = semantics.descriptions(Semantic::from(kind)).size();
        for (auto set = 0U; set < n; ++set) {
            IndexVector indices;
            indices.reserve(m_TriangleCount * 3);
            indexSet.push_back(indices);
        }
    }

    auto &positions = m_table.at(Semantic::POSITION).at(0);
    auto &normals = m_table.at(Semantic::NORMAL).at(0);
    auto &texCoordSets = m_table.at(Semantic::TEXCOORD);
    auto &tangentSets = m_table.at(Semantic::TANGENT);
    auto &colorSets = m_table.at(Semantic::COLOR);

    auto &colorSemantics = semantics.descriptions(Semantic::COLOR);
    auto &texCoordSemantics = semantics.descriptions(Semantic::TEXCOORD);
    auto &tangentSemantics = semantics.descriptions(Semantic::TANGENT);

    const auto colorSetCount = colorSemantics.size();
    const auto texCoordSetCount = texCoordSemantics.size();
    const auto tangentSetCount = tangentSemantics.size();

    const auto numVertices = fnMesh.numVertices(&status);
    THROW_ON_FAILURE(status);

    std::vector<int> localPolygonVertices(numVertices);

    MPointArray triangleVertexPoints;
    MIntArray triangleVertexIndices;
    MIntArray polygonVertexIndices;

    m_triangleToFaceIndexMap.reserve(m_TriangleCount);

    for (MItMeshPolygon itPoly(fnMesh.object()); !itPoly.isDone();
         itPoly.next()) {
        const auto polygonIndex = itPoly.index(&status);
        THROW_ON_FAILURE(status);

        auto numTrianglesInPolygon = 0;
        THROW_ON_FAILURE(itPoly.numTriangles(numTrianglesInPolygon));

        // Map mesh-vertex-indices to face-vertex-indices.
        // TODO: Figure out what Maya API does this for us;
        // we just need the triangles using face-vertex-indices
        THROW_ON_FAILURE(itPoly.getVertices(polygonVertexIndices));
        const int numPolygonVertices = polygonVertexIndices.length();
        for (auto polygonVertexIndex = 0;
             polygonVertexIndex < numPolygonVertices; ++polygonVertexIndex) {
            const auto meshVertexIndex =
                polygonVertexIndices[polygonVertexIndex];
            localPolygonVertices[meshVertexIndex] = polygonVertexIndex;
        }

        THROW_ON_FAILURE(
            itPoly.getTriangles(triangleVertexPoints, triangleVertexIndices));

        const auto numLocalVertices = numTrianglesInPolygon * 3;
        assert(triangleVertexPoints.length() == numLocalVertices);
        assert(triangleVertexIndices.length() == numLocalVertices);

        int triangleVertexIndex = 0;

        for (auto localTriangleIndex = 0;
             localTriangleIndex < numTrianglesInPolygon; ++localTriangleIndex) {
            m_triangleToFaceIndexMap.emplace_back(polygonIndex);

            for (unsigned instanceIndex = 0; instanceIndex < instanceCount;
                 ++instanceIndex) {
                auto &shading = m_shadingPerInstance[instanceIndex];
                const auto shaderIndex = mapPolygonToShaderPerInstance.at(
                    instanceIndex)[polygonIndex];
                shading.primitiveToShaderIndexMap.push_back(shaderIndex);
            }

            for (auto i = 0; i < 3; ++i, ++triangleVertexIndex) {
                const auto meshVertexIndex =
                    triangleVertexIndices[triangleVertexIndex];
                const auto localVertexIndex =
                    localPolygonVertices[meshVertexIndex];

                int positionIndex =
                    itPoly.vertexIndex(localVertexIndex, &status);
                THROW_ON_FAILURE(status);
                positions.push_back(positionIndex);

                int normalIndex = itPoly.normalIndex(localVertexIndex, &status);
                THROW_ON_FAILURE(status);
                normals.push_back(normalIndex);

                for (auto setIndex = 0U; setIndex < colorSetCount; ++setIndex) {
                    int colorIndex;
                    auto &colorSetName = colorSemantics[setIndex].setName;

                    if (itPoly.hasColor(localVertexIndex)) {
                        status = itPoly.getColorIndex(
                            localVertexIndex, colorIndex, &colorSetName);
                        THROW_ON_FAILURE(status);
                        colorSets.at(setIndex).push_back(colorIndex);
                    } else {
                        // This polygon has no associated colors.
                        colorSets.at(setIndex).push_back(NoIndex);
                    }
                }

                for (auto setIndex = 0U; setIndex < texCoordSetCount;
                     ++setIndex) {
                    auto &uvSetName = texCoordSemantics[setIndex].setName;
                    if (itPoly.hasUVs(uvSetName)) {
                        int uvIndex;
                        status = itPoly.getUVIndex(localVertexIndex, uvIndex,
                                                   &uvSetName);
                        THROW_ON_FAILURE(status);
                        texCoordSets.at(setIndex).push_back(uvIndex);
                    } else {
                        texCoordSets.at(setIndex).push_back(NoIndex);
                    }
                }

                for (auto setIndex = 0U; setIndex < tangentSetCount;
                     ++setIndex) {
                    auto &uvSetName = tangentSemantics[setIndex].setName;
                    if (itPoly.hasUVs(uvSetName)) {
                        int uvIndex;
                        status = itPoly.getUVIndex(localVertexIndex, uvIndex,
                                                   &uvSetName);

                        // TODO: Not sure why Maya doesn't allow use to pass the
                        // uvSetName here? Maybe a polygon vertex can only have
                        // a single tangent assigned to it?
                        const auto tangentIndex =
                            itPoly.tangentIndex(localVertexIndex, &status);
                        THROW_ON_FAILURE(status);
                        tangentSets.at(setIndex).push_back(tangentIndex);
                    } else {
                        tangentSets.at(setIndex).push_back(NoIndex);
                    }
                }
            }
        }
    }

    // The indices of the vertex joint assignments are the same as the points.
    // TODO: We should use spans instead of copying the vectors...
    auto &vertexJointWeightsSets = m_table.at(Semantic::WEIGHTS);
    for (auto &set : vertexJointWeightsSets) {
        set = positions;
    }

    auto &vertexJointIndicesSets = m_table.at(Semantic::JOINTS);
    for (auto &set : vertexJointIndicesSets) {
        set = positions;
    }
}

MeshIndices::~MeshIndices() = default;

void MeshIndices::dump(IndentableStream &out, const std::string &name) const {
    dump_index_table(out, name, m_table, perPrimitiveVertexCount());
}
