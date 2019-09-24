#pragma once

#include "macros.h"
#include "sceneTypes.h"

class MeshSkeleton;

struct VertexElementSetDescription {
    VertexElementSetDescription(const Semantic::Kind semantic,
                                const SetIndex setIndex, const MString &setName,
                                const int elementCount)
        : semantic(semantic), setName(setName), setIndex(setIndex),
          elementCount(elementCount) {}

    DEFAULT_COPY_MOVE_ASSIGN_DTOR(VertexElementSetDescription);

    void dump(class IndentableStream &out, const std::string &name) const;

    Semantic::Kind semantic;
    MString setName;
    SetIndex setIndex;
    int elementCount;
};

typedef std::vector<VertexElementSetDescription>
    VertexComponentSetDescriptionPerSetIndex;
typedef std::array<VertexComponentSetDescriptionPerSetIndex, Semantic::COUNT>
    VertexComponentSetDescriptionPerSetIndexTable;

class MeshSemantics {
  public:
    // Skeleton is needed to determine if the skin weight/joint semantics are
    // needed.
    MeshSemantics(const MFnMesh &mesh, MeshSkeleton *skeleton,
                  const MeshSemanticSet &semanticSet);
    virtual ~MeshSemantics();

    const VertexComponentSetDescriptionPerSetIndexTable &table() const {
        return m_table;
    }

    const VertexComponentSetDescriptionPerSetIndex &
    descriptions(const Semantic::Kind kind) const {
        return m_table.at(kind);
    }

    void dump(class IndentableStream &cout, const std::string &name) const;

  private:
    DISALLOW_COPY_MOVE_ASSIGN(MeshSemantics);
    VertexComponentSetDescriptionPerSetIndexTable m_table;
};
