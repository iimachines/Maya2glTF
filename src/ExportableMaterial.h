#pragma once
#include "sceneTypes.h"
#include "color.h"

class ExportableResources;

class ExportableMaterial
{
public:
	virtual ~ExportableMaterial() = 0;

	virtual GLTF::Material* glMaterial() = 0;

	static std::unique_ptr<ExportableMaterial> from(ExportableResources& resources, const MFnDependencyNode& shaderNode);

protected:
	static bool getScalar(const MObject& shaderObject, const char* attributeName, float& scalar);
	static bool getColor(const MObject& shaderObject, const char* attributeName, Float4& color);
};

class ExportableMaterialBasePBR : public ExportableMaterial
{
public:
	GLTF::Material* glMaterial() override { return &m_pbrMaterial; }

protected:
	Float4 m_pbrBaseColorFactor;
	Float3 m_pbrEmissiveFactor;
	GLTF::MaterialPBR m_pbrMaterial;
	GLTF::MaterialPBR::MetallicRoughness m_pbrMetallicRoughness;
};

class ExportableDefaultMaterial : public ExportableMaterialBasePBR
{
public:
	ExportableDefaultMaterial();
	~ExportableDefaultMaterial();
};

class ExportableMaterialPBR : public ExportableMaterialBasePBR
{
public:
	ExportableMaterialPBR(ExportableResources& resources, const MFnDependencyNode& shaderNode);
	~ExportableMaterialPBR();
};

class ExportableDebugMaterial : public ExportableMaterialBasePBR
{
public:
	ExportableDebugMaterial(const Float3& hsv);
	~ExportableDebugMaterial();
};
