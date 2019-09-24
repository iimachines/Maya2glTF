#pragma once

#include "MeshShape.h"

class ExportableNode;
class Arguments;

typedef std::vector<MeshShape *> MeshShapes;

class Mesh {
  public:
    Mesh(ExportableScene &scene, MDagPath dagPath, const ExportableNode &node);
    ~Mesh();

    void dump(IndentableStream &out, const std::string &name) const;

    bool isEmpty() const { return m_allShapes.empty(); }

    const MainShape &shape() const { return *m_mainShape; }
    const MeshShapes &allShapes() const { return m_allShapes; }

  private:
    DISALLOW_COPY_MOVE_ASSIGN(Mesh);

    struct Cleanup {
        ~Cleanup();
        MObject tempOutputMesh;
    };

    std::unique_ptr<MainShape> m_mainShape;
    std::vector<std::unique_ptr<MeshShape>> m_blendShapes;
    MeshShapes m_allShapes;

    Cleanup m_cleanup;

    MObject getOrCreateOutputShape(MPlug &outputGeometryPlug,
                                   MObject &createdMesh) const;

    static MObject
    tryExtractBlendShapeDeformer(const MFnMesh &fnMesh,
                                 const MSelectionList &ignoredDeformers);
};
