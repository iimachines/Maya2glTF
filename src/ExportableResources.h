#pragma once
#include "ExportableItem.h"
#include "ExportableMaterial.h"
#include "filesystem.h"

class Arguments;
typedef std::string MayaFilename;
typedef std::string MayaNodeName;

class ExportableMaterial;
class ExportableMesh;

enum ImageTilingFlags { IMAGE_TILING_Wrap = 1, IMAGE_TILING_Mirror = 2 };

enum ImageFilterKind {
    IMAGE_FILTER_Off = 0,
    IMAGE_FILTER_MipMap = 1,
    IMAGE_FILTER_Box = 2,
    IMAGE_FILTER_Quadratic = 3,
    IMAGE_FILTER_Quartic = 4,
    IMAGE_FILTER_Gaussian = 5
};

class ExportableResources : public ExportableItem {
  public:
    ExportableResources(const Arguments &args);
    ~ExportableResources();

    const Arguments &arguments() const { return m_args; }

    ExportableMaterial *getDefaultMaterial() { return &m_defaultMaterial; }
    ExportableMaterial *getDebugMaterial(const Float3 &hue);
    ExportableMaterial *getMaterial(const MObject &shaderGroup);

    GLTF::Image *getImage(fs::path path);

    GLTF::Sampler *getSampler(const ImageFilterKind filter,
                              const ImageTilingFlags uTiling,
                              const ImageTilingFlags vTiling);

    GLTF::Texture *getTexture(GLTF::Image *image, GLTF::Sampler *sampler);

    // std::map<MayaFilename, std::unique_ptr<GLTF::Image>> imageMap;
    // std::map<MayaNodeName, std::unique_ptr<GLTF::Texture>> textureMap;
    // std::map<MayaNodeName, std::unique_ptr<GLTF::Sampler>> samplerMap;

    void getAllAccessors(std::vector<GLTF::Accessor *> &accessors);

  private:
    std::map<MayaNodeName, std::unique_ptr<ExportableMaterial>> m_materialMap;
    std::map<Float3, std::unique_ptr<ExportableMaterial>> m_debugMaterialMap;
    std::map<std::string, std::unique_ptr<GLTF::Image>> m_imageMap;
    std::map<int, std::unique_ptr<GLTF::Sampler>> m_samplerMap;
    std::map<std::pair<GLTF::Image *, GLTF::Sampler *>,
             std::unique_ptr<GLTF::Texture>>
        m_TextureMap;

    ExportableDefaultMaterial m_defaultMaterial;
    const Arguments &m_args;
};
