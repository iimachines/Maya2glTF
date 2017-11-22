#pragma once
#include "ExportableItem.h"
#include "ExportableMaterial.h"

class Arguments;
typedef std::string MayaFilename;
typedef std::string MayaNodeName;

class ExportableMaterial;
class ExportableMesh;

class ExportableResources : public ExportableItem
{
public:
	ExportableResources(const Arguments& args);
	~ExportableResources();

	const Arguments& arguments() const { return m_args; }

	ExportableMaterial* getDefaultMaterial() { return &m_defaultMaterial; }
	ExportableMaterial* getDebugMaterial(const Float3& hue);
	ExportableMaterial* getMaterial(const MObject& shaderGroup);

	//std::map<MayaFilename, std::unique_ptr<GLTF::Image>> imageMap;
	//std::map<MayaNodeName, std::unique_ptr<GLTF::Texture>> textureMap;
	//std::map<MayaNodeName, std::unique_ptr<GLTF::Sampler>> samplerMap;

private:
	std::map<MayaNodeName, std::unique_ptr<ExportableMaterial>> m_materialMap;
	std::map<Float3, std::unique_ptr<ExportableMaterial>> m_debugMaterialMap;

	ExportableDefaultMaterial m_defaultMaterial;
	const Arguments& m_args;
};

