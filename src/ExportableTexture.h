#pragma once

#include "macros.h"
class ExportableResources;

class ExportableTexture
{
public:
	ExportableTexture(ExportableResources& resources, const MObject& obj, const char* attributeName);
	virtual ~ExportableTexture();

	GLTF::Texture* glTexture;
	GLTF::Sampler* glSampler;

	MObject connectedObject;
	MString imageFilePath;

	operator GLTF::Texture*() const { return glTexture; }

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableTexture);
};
