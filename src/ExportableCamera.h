#pragma once

#include "ExportableObject.h"
#include "basicTypes.h"

class ExportableResources;
class ExportablePrimitive;
class Arguments;
class ExportableScene;
class ExportableNode;

class ExportableCamera : public ExportableObject {
  public:
    // TODO: Support instancing, for now we create a new camera for each node.
    ExportableCamera(ExportableScene &scene, ExportableNode &node,
                     const MDagPath &shapeDagPath);
    virtual ~ExportableCamera();

    std::unique_ptr<GLTF::Camera> glCamera;

    void attachToNode(GLTF::Node &node) const;

  private:
    DISALLOW_COPY_MOVE_ASSIGN(ExportableCamera);
};
