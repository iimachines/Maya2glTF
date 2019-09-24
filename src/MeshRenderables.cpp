#include "MeshRenderables.h"
#include "Arguments.h"
#include "IndentableStream.h"
#include "Mesh.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "externals.h"

using namespace coveo::linq;

MeshRenderables::MeshRenderables(const MeshShapes &meshShapes,
                                 const Arguments &args)
    : instanceNumber(meshShapes.at(0)->instanceNumber()) {
    MStatus status;

    const auto &mainShape = dynamic_cast<MainShape *>(meshShapes.at(0));
    const auto &mainIndices = mainShape->indices();
    const auto &mainVertices = mainShape->vertices();
    const auto &mainIndicesTable = mainIndices.table();
    const auto &mainVerticesTable = mainVertices.table();

    auto &shadingPerInstance = mainIndices.shadingPerInstance();

    auto &shading = shadingPerInstance.at(instanceNumber);

    const auto primitiveCount = mainIndices.primitiveCount();
    const auto maxVertexCount = mainIndices.maxVertexCount();
    const auto minVertexCount = mainShape->semantics()
                                    .descriptions(Semantic::POSITION)
                                    .at(0)
                                    .elementCount;
    const auto perPrimitiveVertexCount = mainIndices.perPrimitiveVertexCount();

    auto primitiveVertexIndex = 0;

    VertexElementData vertexIndexKey;
    VertexLayout vertexLayout;

    const auto semanticsMask = args.meshPrimitiveAttributes;

    auto totalWeldCount = 0;
    auto totalVertexCount = 0;

    for (auto primitiveIndex = 0; primitiveIndex < primitiveCount;
         ++primitiveIndex) {
        const auto shaderIndex =
            shading.primitiveToShaderIndexMap[primitiveIndex];

        for (int counter = perPrimitiveVertexCount; --counter >= 0;
             ++primitiveVertexIndex) {
            // Compute the vertex signature (one bit per semantic+set, 0=unused,
            // 1=used)
            VertexSignature vertexSignature(shaderIndex, 0);

            vertexLayout.clear();
            vertexIndexKey.clear();

            for (auto shapeIndex = 0U; shapeIndex < meshShapes.size();
                 ++shapeIndex) {
                auto &shape = meshShapes.at(shapeIndex);
                const auto &shapeVerticesTable = shape->vertices().table();

                for (auto semanticIndex = 0U;
                     semanticIndex < shapeVerticesTable.size();
                     ++semanticIndex) {
                    if (!shapeVerticesTable.at(semanticIndex).empty() &&
                        semanticsMask.test(semanticIndex)) {
                        const auto &indicesPerSet =
                            mainIndicesTable.at(semanticIndex);

                        for (auto setIndex = 0; setIndex < indicesPerSet.size();
                             ++setIndex) {
                            const auto &indices = indicesPerSet.at(setIndex);
                            const auto index = indices[primitiveVertexIndex];
                            const int isUsed = index >= 0;
                            vertexSignature.slotUsage <<= 1;
                            vertexSignature.slotUsage |= isUsed;
                            if (isUsed) {
                                auto semantic = Semantic::from(semanticIndex);
                                vertexLayout.emplace_back(
                                    ShapeIndex::shape(shapeIndex), semantic,
                                    setIndex);

                                const auto &elementIndices =
                                    indicesPerSet.at(setIndex);
                                const auto vertexIndex =
                                    elementIndices.at(primitiveVertexIndex);
                                const auto &vertexElements =
                                    shapeVerticesTable.at(semantic).at(
                                        setIndex);
                                const auto &sourceComponents =
                                    componentsAt(vertexElements, vertexIndex,
                                                 semantic, shape->shapeIndex);
                                const auto sourceBytes =
                                    sourceComponents.bytes();
                                vertexIndexKey.insert(vertexIndexKey.end(),
                                                      sourceBytes.begin(),
                                                      sourceBytes.end());
                            }
                        }
                    }
                }
            }

            // Check if a vertex with exactly the same components already
            // exists.
            VertexBuffer &vertexBuffer = m_table[vertexSignature];

            auto &componentsMap = vertexBuffer.componentsMap;

            VertexIndex sharedVertexIndex;

            const auto itSharedIndex =
                vertexBuffer.vertexToIndexMapping.find(vertexIndexKey);

            if (itSharedIndex == vertexBuffer.vertexToIndexMapping.end()) {
                // No vertex with same indices found, create a new output vertex
                // index.
                sharedVertexIndex = static_cast<VertexIndex>(
                    vertexBuffer.vertexToIndexMapping.size());
                vertexBuffer.vertexToIndexMapping[vertexIndexKey] =
                    sharedVertexIndex;

                // Build the vertex.
                for (auto &&slot : vertexLayout) {
                    auto &shape = meshShapes.at(slot.shapeIndex.arrayIndex());

                    const auto &elementIndices =
                        mainIndices.indicesAt(slot.semantic, slot.setIndex);
                    const auto vertexIndex =
                        elementIndices.at(primitiveVertexIndex);
                    const auto &vertexElements =
                        shape->vertices().vertexElementComponentsAt(
                            slot.semantic, slot.setIndex);
                    const auto &sourceComponents =
                        componentsAt(vertexElements, vertexIndex, slot.semantic,
                                     slot.shapeIndex);
                    const auto sourceBytes = sourceComponents.bytes();
                    auto &target = componentsMap[slot];
                    if (target.empty()) {
                        target.reserve(maxVertexCount * slot.elementByteSize());
                    }

                    target.insert(target.end(), sourceBytes.begin(),
                                  sourceBytes.end());
                }
            } else {
                // Reuse the same vertex.
                sharedVertexIndex = itSharedIndex->second;

                ++totalWeldCount;
            }

            vertexBuffer.indices.push_back(sharedVertexIndex);
        }
    }

    cout << prefix << mainShape->dagPath().partialPathName().asChar()
         << " will have " << maxVertexCount - totalWeldCount
         << " vertices. Welded#" << totalWeldCount << ", min#" << minVertexCount
         << ", max#" << maxVertexCount << endl;

    // Now compute the blend-shape vector-deltas by subtracting the
    // blend-shape-base mesh from the blend-shape-targets
    if (meshShapes.size() > 1) {
        for (auto &&pair : m_table) {
            VertexBuffer &buffer = pair.second;
            VertexElementsMap &compMap = buffer.componentsMap;

            for (auto &&slotCompPair : compMap) {
                auto &targetSlot = slotCompPair.first;

                if (targetSlot.shapeIndex.isBlendShapeIndex()) {
                    const VertexSlot mainSlot(ShapeIndex::main(),
                                              targetSlot.semantic,
                                              targetSlot.setIndex);
                    auto sourceComponents =
                        reinterpret_span<float>(compMap.at(mainSlot));
                    auto targetComponents = mutable_span(
                        reinterpret_span<float>(slotCompPair.second));

                    // The annoying fact that TANGENTs have dimension 4 in the
                    // main shape and 3 in the targets requires this hacky code.
                    const auto sourceDimension = mainSlot.dimension();
                    const auto targetDimension = targetSlot.dimension();
                    const auto sharedDimension =
                        std::min(sourceDimension, targetDimension);
                    const auto sourceComponentCount = sourceComponents.size();
                    const auto targetComponentCount = targetComponents.size();
                    assert(sourceComponentCount / sourceDimension ==
                           targetComponentCount / targetDimension);

                    for (size_t sourceIndex = 0U, targetIndex = 0U;
                         sourceIndex < size_t(sourceComponentCount);
                         sourceIndex += sourceDimension,
                                targetIndex += targetDimension) {
                        for (size_t dimension = 0; dimension < sharedDimension;
                             ++dimension) {
                            targetComponents[targetIndex + dimension] -=
                                sourceComponents[sourceIndex + dimension];
                        }
                    }
                }
            }
        }
    }
}

MeshRenderables::~MeshRenderables() = default;

std::ostream &operator<<(std::ostream &out, const VertexSignature &obj) {
    out << '{' << ' ';
    out << std::quoted("shaderIndex") << ':' << obj.shaderIndex << ',';
    out << std::quoted("slotUsage") << ':' << std::hex << std::setw(8)
        << obj.slotUsage;
    out << ' ' << '}';
    return out;
}

std::ostream &operator<<(std::ostream &out, const VertexSlot &slot) {
    out << '{' << ' ';
    out << std::quoted("shapeIndex") << ':' << slot.shapeIndex << ',' << ' ';
    out << std::quoted("setIndex") << ':' << slot.setIndex << ',' << ' ';
    out << std::quoted("semantic") << ':'
        << std::quoted(Semantic::name(slot.semantic));
    out << ' ' << '}';
    return out;
}

// std::ostream& operator<<(std::ostream& out, const VertexBuffer& obj)
//{
//	out << '{' << endl << indent;
//
//	dump_iterable(out, "indices", obj.indices, obj.indices.size() /
//obj.vertexToIndexMapping.size(), 0);
//
//	out << "," << endl;
//
//	dump_iterable(out, "components", obj.componentsMap, 1);
//
//	out << undent << '}';
//
//	return out;
//}
//
