#pragma once

#include "ExportableMaterial.h"
#include "ExportableMesh.h"
#include "MeshRenderables.h"
#include "sceneTypes.h"

typedef std::vector<std::unique_ptr<GLTF::Primitive::Target>>
    BlendShapeToTargetTable;

class ExportableResources;

class ExportablePrimitive {
  public:
    ExportablePrimitive(const std::string &name,
                        const VertexBuffer &vertexBuffer,
                        ExportableResources &resources,
                        ExportableMaterial *material);

    ExportablePrimitive(const std::string &name,
                        const VertexBuffer &vertexBuffer,
                        ExportableResources &resources,
                        Semantic::Kind debugSemantic,
                        const ShapeIndex &debugShapeIndex,
                        double debugLineLength, Color debugLineColor);

    virtual ~ExportablePrimitive();

    GLTF::Primitive glPrimitive;
    std::unique_ptr<GLTF::Accessor> glIndices;
    BlendShapeToTargetTable glTargetTable;

    void getAllAccessors(std::vector<GLTF::Accessor *> &accessors) const;

  private:
    std::vector<std::unique_ptr<GLTF::Accessor>> glAccessors;

    DISALLOW_COPY_MOVE_ASSIGN(ExportablePrimitive);
};
