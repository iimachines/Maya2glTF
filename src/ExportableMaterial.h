#pragma once
#include "ExportableResources.h"

class ExportableMaterial
{
public:
	virtual ~ExportableMaterial() = 0;

	virtual GLTF::Material* glMaterial() = 0;

	static std::unique_ptr<ExportableMaterial> from(const MFnDependencyNode& shaderNode);

protected:
	static bool getScalar(const MObject& shaderObject, const char* attributeName, float& scalar);
	static bool getColor(const MObject& shaderObject, const char* attributeName, Float4& color);
};

class ExportableMaterialPBR : public ExportableMaterial
{
public:
	ExportableMaterialPBR(const MFnDependencyNode& shaderNode);
	~ExportableMaterialPBR();

	GLTF::Material* glMaterial() override { return &m_pbrMaterial; }

private:
	Float4 m_pbrBaseColorFactor;
	Float3 m_pbrEmissiveFactor;
	GLTF::MaterialPBR m_pbrMaterial;
	GLTF::MaterialPBR::MetallicRoughness m_pbrMetallicRoughness;
};

