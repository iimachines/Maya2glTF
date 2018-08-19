#pragma once

#include "macros.h"
#include "color.h"

class ExportableResources;

class ExportableMaterial
{
public:
	ExportableMaterial();
	virtual ~ExportableMaterial() = 0;

	virtual GLTF::Material* glMaterial() = 0;

	virtual bool hasTextures() const = 0;

	static std::unique_ptr<ExportableMaterial> from(ExportableResources& resources, const MFnDependencyNode& shaderNode);

protected:
	//static bool tryCreateTexture(ExportableResources& resources, const MObject& obj, const char* attributeName, GLTF::Texture*& outputTexture, MString& outputTexturePath);
	//static bool tryCreateTexture(ExportableResources& resources, const MObject& obj, const char* attributeName, GLTF::Texture*& outputTexture);
	static bool tryCreateNormalTexture(ExportableResources& resources, const MObject& obj, float& normalScale, GLTF::Texture*& outputTexture);

	static bool getScalar(const MObject& shaderObject, const char* attributeName, float& scalar);
	static bool getColor(const MObject& shaderObject, const char* attributeName, Float4& color);
	static bool getString(const MObject& shaderObject, const char* attributeName, MString& string);
	static bool getBoolean(const MObject& shaderObject, const char* attributeName, bool& result);

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableMaterial);
};

class ExportableMaterialBasePBR : public ExportableMaterial
{
public:
	ExportableMaterialBasePBR();
	virtual ~ExportableMaterialBasePBR();

	GLTF::Material* glMaterial() override { return &m_glMaterial; }

	bool hasTextures() const override;

protected:
	Float4 m_glBaseColorFactor;
	Float4 m_glEmissiveFactor;
	GLTF::MaterialPBR m_glMaterial;
	GLTF::MaterialPBR::MetallicRoughness m_glMetallicRoughness;
	
	GLTF::MaterialPBR::Texture m_glBaseColorTexture;
	GLTF::MaterialPBR::Texture m_glMetallicRoughnessTexture;
	GLTF::MaterialPBR::Texture m_glNormalTexture;
	GLTF::MaterialPBR::Texture m_glEmissiveTexture;
	GLTF::MaterialPBR::Texture m_glOcclusionTexture;

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableMaterialBasePBR);
};

class ExportableDefaultMaterial : public ExportableMaterialBasePBR
{
public:
	ExportableDefaultMaterial();
	~ExportableDefaultMaterial();

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableDefaultMaterial);
};

class ExportableMaterialPBR : public ExportableMaterialBasePBR
{
public:
	ExportableMaterialPBR(ExportableResources& resources, const MFnDependencyNode& shaderNode);
	~ExportableMaterialPBR();

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableMaterialPBR);

	void loadPBR(ExportableResources& resources, const MFnDependencyNode& shaderNode);

	template<class MFnShader> void convert(ExportableResources& resources, const MObject& shaderObject);
};

class ExportableDebugMaterial : public ExportableMaterialBasePBR
{
public:
	ExportableDebugMaterial(const Float3& hsv);
	~ExportableDebugMaterial();

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableDebugMaterial);

};

