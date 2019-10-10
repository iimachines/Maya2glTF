#pragma once

#include "macros.h"
class ExportableResources;

/** The ExportableTexture just creates textures and samples in the resources, it
 * does not own them! */
class ExportableTexture {
    struct Private {};

  public:
    static std::unique_ptr<ExportableTexture>
    tryCreate(ExportableResources &resources, const MObject &obj,
              const char *attributeName);

    static GLTF::Texture *tryLoad(ExportableResources &resources,
                                  const MObject &obj,
                                  const char *attributeName);

    virtual ~ExportableTexture();

    GLTF::Texture *glTexture = nullptr;
    GLTF::Sampler *glSampler = nullptr;

    MObject connectedObject;
    MString imageFilePath;

    ExportableTexture(Private, ExportableResources &resources,
                      const MObject &obj, const char *attributeName);

  private:
    ExportableTexture() = default;
    DISALLOW_COPY_MOVE_ASSIGN(ExportableTexture);
};
