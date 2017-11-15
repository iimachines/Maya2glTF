#pragma once
#include "ExportableItem.h"

typedef std::string MayaFilename;
typedef std::string MayaNodeName;

class ExportableMaterial;

class ExportableResources : public ExportableItem
{
public:
	ExportableResources();
	~ExportableResources();

	ExportableMaterial* getMaterial(const MObject& shaderGroup);

	std::map<MayaNodeName, std::unique_ptr<ExportableMaterial>> materialMap;
	//std::map<MayaFilename, std::unique_ptr<GLTF::Image>> imageMap;
	//std::map<MayaNodeName, std::unique_ptr<GLTF::Texture>> textureMap;
	//std::map<MayaNodeName, std::unique_ptr<GLTF::Sampler>> samplerMap;

};

