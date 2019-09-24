#include "MeshSemantics.h"
#include "IndentableStream.h"
#include "MayaException.h"
#include "MeshSkeleton.h"
#include "externals.h"

void VertexElementSetDescription::dump(class IndentableStream &out,
                                       const std::string &name) const {
    out << std::quoted(name) << ": {" << endl << indent;

    out << std::quoted("setName") << ": " << std::quoted(setName.asChar())
        << "," << endl;
    out << std::quoted("setIndex") << ": " << setIndex << "," << endl;
    out << std::quoted("elementCount") << ": " << elementCount << endl;

    out << undent << '}';
}

MeshSemantics::MeshSemantics(const MFnMesh &mesh, MeshSkeleton *skeleton,
                             const MeshSemanticSet &semanticSet) {
    MStatus status;

    auto numVertices = mesh.numVertices(&status);

    m_table[Semantic::POSITION].emplace_back(Semantic::POSITION, 0, "",
                                             numVertices);
    THROW_ON_FAILURE(status);

    m_table[Semantic::NORMAL].emplace_back(Semantic::NORMAL, 0, "",
                                           mesh.numNormals(&status));
    THROW_ON_FAILURE(status);

    MStringArray colorSetNames;
    THROW_ON_FAILURE(mesh.getColorSetNames(colorSetNames));

    for (SetIndex i = 0; i < SetIndex(colorSetNames.length()); ++i) {
        m_table[Semantic::COLOR].emplace_back(
            Semantic::COLOR, i, colorSetNames[i].asChar(),
            mesh.numColors(colorSetNames[i], &status));
        THROW_ON_FAILURE(status);
    }

    MStringArray uvSetNames;
    THROW_ON_FAILURE(mesh.getUVSetNames(uvSetNames));

    for (SetIndex i = 0; i < SetIndex(uvSetNames.length()); ++i) {
        m_table[Semantic::TEXCOORD].emplace_back(
            Semantic::TEXCOORD, i, uvSetNames[i].asChar(),
            mesh.numUVs(uvSetNames[i], &status));

        // We don't process tangents unless requested.
        if (semanticSet.test(Semantic::TANGENT))
            m_table[Semantic::TANGENT].emplace_back(
                Semantic::TANGENT, i, uvSetNames[i].asChar(),
                mesh.numUVs(uvSetNames[i], &status));
    }

    // Add skin semantics
    if (skeleton) {
        const auto vertexJointAssignmentSetCount =
            skeleton->vertexJointAssignmentSetCount();

        for (SetIndex i = 0; i < SetIndex(vertexJointAssignmentSetCount); ++i) {
            m_table[Semantic::WEIGHTS].emplace_back(
                Semantic::WEIGHTS, i,
                MString(name(Semantic::WEIGHTS)) + "_" + i, numVertices);
            m_table[Semantic::JOINTS].emplace_back(
                Semantic::JOINTS, i, MString(name(Semantic::JOINTS)) + "_" + i,
                numVertices);
        }
    }
}

MeshSemantics::~MeshSemantics() = default;

void MeshSemantics::dump(class IndentableStream &out,
                         const std::string &name) const {
    out << quoted(name) << ": {" << endl << indent;

    JsonSeparator sep(",\n");

    for (int semanticIndex = 0; semanticIndex < Semantic::COUNT;
         ++semanticIndex) {
        const auto semanticKind = Semantic::from(semanticIndex);

        for (auto &&semantic : m_table.at(semanticKind)) {
            out << sep;
            semantic.dump(out, Semantic::name(semanticKind));
        }
    }

    out << endl << undent << '}';
}
