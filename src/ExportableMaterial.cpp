#include "externals.h"
#include "ExportableMaterial.h"
#include "DagHelper.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "Arguments.h"

ExportableMaterial::~ExportableMaterial()
{
}

std::unique_ptr<ExportableMaterial> ExportableMaterial::from(ExportableResources& resources, const MFnDependencyNode& shaderNode)
{
	if (shaderNode.typeName() == "GLSLShader" || resources.arguments().forcePbrMaterials)
		return std::make_unique<ExportableMaterialPBR>(resources, shaderNode);

	cerr << prefix 
		<< "WARNING: unsupported shader node type: " << shaderNode.typeName().asChar() << " #" << shaderNode.type() 
		<< "Either use the Maya2glTF GLSLShader, or pass the -forcePbrMaterials (-fpm) flag"
		<< endl;

	return nullptr;
}

bool ExportableMaterial::tryCreateTexture(
	ExportableResources& resources,
	const MObject& obj,
	const char* attributeName,
	GLTF::Texture* &texturePtr)
{
	MObject fileTextureObj = DagHelper::findNodeConnectedTo(obj, attributeName);
	if (fileTextureObj.isNull())
		return false;

	const auto apiType = fileTextureObj.apiType();
	if (apiType != MFn::kFileTexture)
	{
		cout << "WARNING: Unsupported texture node '" << fileTextureObj.apiTypeStr() << " #" << apiType << endl;
		return false;
	}

	MString filename;
	if (!DagHelper::getPlugValue(fileTextureObj, "fileTextureName", filename))
		return false;

	int filterType = IMAGE_FILTER_MipMap;
	DagHelper::getPlugValue(fileTextureObj, "filterType", filterType);

	int uWrap = false;
	int vWrap = false;
	int uMirror = false;
	int vMirror = false;

	DagHelper::getPlugValue(fileTextureObj, "wrapU", uWrap);
	DagHelper::getPlugValue(fileTextureObj, "wrapV", vWrap);
	DagHelper::getPlugValue(fileTextureObj, "mirrorU", uMirror);
	DagHelper::getPlugValue(fileTextureObj, "mirrorV", vMirror);

	cout << prefix << "Found texture '" << filename << "'" 
		<< " with filter type = " << filterType 
		<< ", image wrapping = " << uWrap << " " << vWrap << ", mirror = " << uMirror << " " << vMirror << endl;

	const auto imagePtr = resources.getImage(filename.asChar());
	if (!imagePtr)
		return false;

	auto uTiling = uWrap * IMAGE_TILING_Wrap + uMirror * IMAGE_TILING_Mirror;
	auto vTiling = vWrap * IMAGE_TILING_Wrap + vMirror * IMAGE_TILING_Mirror;

	auto samplerPtr = resources.getSampler(
		static_cast<ImageFilterKind>(filterType),
		static_cast<ImageTilingFlags>(uTiling),
		static_cast<ImageTilingFlags>(vTiling));
	assert(samplerPtr);

	texturePtr = resources.getTexture(imagePtr, samplerPtr);
	assert(texturePtr);

	return true;
}

bool ExportableMaterial::tryCreateNormalTexture(
	ExportableResources& resources, 
	const MObject& shaderObject,
	float& normalScale, 
	GLTF::Texture*& outputTexture)
{
	MObject normalCamera = DagHelper::findSourceNodeConnectedTo(shaderObject, "normalCamera");
	if (normalCamera.isNull())
		return false;

	if (!getScalar(normalCamera, "bumpDepth", normalScale))
		return false;

	if (!tryCreateTexture(resources, normalCamera, "bumpValue", outputTexture))
		return false;

	return true;

}

bool ExportableMaterial::getScalar(const MObject& obj, const char* attributeName, float& scalar)
{
	return DagHelper::getPlugValue(obj, attributeName, scalar);
}

bool ExportableMaterial::getColor(const MObject& obj, const char* attributeName, Float4& color)
{
	MColor c;
	if (!DagHelper::getPlugValue(obj, attributeName, c))
		return false;

	color = { c.r, c.g, c.b, c.a };
	return true;
}

ExportableMaterialPBR::ExportableMaterialPBR(ExportableResources& resources, const MFnDependencyNode& shaderNode)
{
	MStatus status;

	const auto shaderObject = shaderNode.object(&status);
	THROW_ON_FAILURE(status);

	const auto shaderType = shaderObject.apiType();

	switch (shaderType)
	{
	case MFn::kPhong:
		convert<MFnPhongShader>(resources, shaderObject);
		break;
	case MFn::kLambert:
		convert<MFnLambertShader>(resources, shaderObject);
		break;
	case MFn::kBlinn:
		convert<MFnBlinnShader>(resources, shaderObject);
		break;
	case MFn::kPluginHardwareShader:
		loadPBR(resources, shaderObject);
		break;
	default:
		cerr << prefix << "WARNING: skipping unsupported PBR shader type '" << shaderObject.apiTypeStr() << "' #" << shaderType << endl;
		break;
	}
}

template<class MFnShader> 
void ExportableMaterialPBR::convert(ExportableResources& resources, const MObject& shaderObject)
{
	MStatus status;

	MFnShader shader(shaderObject, &status);
	THROW_ON_FAILURE(status);

	m_glMetallicRoughness.roughnessFactor = 1;
	m_glMetallicRoughness.metallicFactor = 0;
	m_glMaterial.metallicRoughness = &m_glMetallicRoughness;

	GLTF::Texture* colorTexture = nullptr;
	if (tryCreateTexture(resources, shaderObject, "color", colorTexture))
	{
		m_glBaseColorTexture.texture = colorTexture;
		m_glMetallicRoughness.baseColorTexture = &m_glBaseColorTexture;
	}

	// TODO: Currently we expect the alpha channel of the color texture to hold the transparency.
	const bool hasTransparencyTexture = shader.findPlug("transparency").isConnected();

	const auto color = colorTexture ? MColor(1,1,1) : shader.color(&status);

	const auto diffuseFactor = shader.diffuseCoeff(&status);
	const auto transparency = hasTransparencyTexture ? 0 : shader.transparency(&status).r;

	// TODO: Currently we don't actually check the pixels of the transparency texture.
	const auto isTransparent = hasTransparencyTexture || transparency != 0;
	if (isTransparent)
	{
		m_glMaterial.alphaMode = "BLEND";
	}

	// TODO: Support MASK alphaMode and alphaCutoff
	
	// TODO: Support double-sides materials.

	m_glBaseColorFactor = 
	{ 
		color.r * diffuseFactor, 
		color.g * diffuseFactor, 
		color.b * diffuseFactor, 
		1 - transparency 
	};

	m_glMetallicRoughness.baseColorFactor = &m_glBaseColorFactor[0];

	// Normal
	float normalScale;
	GLTF::Texture* normalTexture;
	if (tryCreateNormalTexture(resources, shaderObject, normalScale, normalTexture))
	{
		m_glNormalTexture.texture = normalTexture;
		m_glNormalTexture.scale = normalScale;
		// TODO: m_glNormalTexture.texCoord = ...
		m_glMaterial.normalTexture = &m_glNormalTexture;
	}
}



void ExportableMaterialPBR::loadPBR(ExportableResources& resources, const MFnDependencyNode& shaderNode)
{
	/*
	u_OcclusionTexture_Name
	u_OcclusionTexture_Type
	u_OcclusionTexture
	u_OcclusionTextureR
	u_OcclusionTextureG
	u_OcclusionTextureB
	u_OcclusionStrength_Name
	u_OcclusionStrength_Type
	u_OcclusionStrength
	u_BaseColorFactor_Name
	u_BaseColorFactor_Type
	u_BaseColorFactor
	u_BaseColorFactorRGB
	u_BaseColorFactorR
	u_BaseColorFactorG
	u_BaseColorFactorB
	u_BaseColorFactorA
	u_ScaleDiffBaseMR_Name
	u_ScaleDiffBaseMR_Type
	u_ScaleDiffBaseMR
	u_ScaleDiffBaseMRXYZ
	u_ScaleDiffBaseMRX
	u_ScaleDiffBaseMRY
	u_ScaleDiffBaseMRZ
	u_ScaleDiffBaseMRW
	u_ScaleFGDSpec_Name
	u_ScaleFGDSpec_Type
	u_ScaleFGDSpec
	u_ScaleFGDSpecXYZ
	u_ScaleFGDSpecX
	u_ScaleFGDSpecY
	u_ScaleFGDSpecZ
	u_ScaleFGDSpecW
	u_LightDir_Name
	u_LightDir_Type
	u_LightDir
	u_LightDirX
	u_LightDirY
	u_LightDirZ
	u_NormalTexture_Name
	u_NormalTexture_Type
	u_NormalTexture
	u_NormalTextureR
	u_NormalTextureG
	u_NormalTextureB
	u_NormalScale_Name
	u_NormalScale_Type
	u_NormalScale
	u_DiffuseEnvTexture_Name
	u_DiffuseEnvTexture_Type
	u_DiffuseEnvTexture
	u_DiffuseEnvTextureR
	u_DiffuseEnvTextureG
	u_DiffuseEnvTextureB
	u_SpecularEnvTexture_Name
	u_SpecularEnvTexture_Type
	u_SpecularEnvTexture
	u_SpecularEnvTextureR
	u_SpecularEnvTextureG
	u_SpecularEnvTextureB
	u_brdfTexture_Name
	u_brdfTexture_Type
	u_brdfTexture
	u_brdfTextureR
	u_brdfTextureG
	u_brdfTextureB
	u_MetallicTexture_Name
	u_MetallicTexture_Type
	u_MetallicTexture
	u_MetallicTextureR
	u_MetallicTextureG
	u_MetallicTextureB
	u_MetallicStrength_Name
	u_MetallicStrength_Type
	u_MetallicStrength
	u_RoughnessTexture_Name
	u_RoughnessTexture_Type
	u_RoughnessTexture
	u_RoughnessTextureR
	u_RoughnessTextureG
	u_RoughnessTextureB
	u_RoughnessStrength_Name
	u_RoughnessStrength_Type
	u_RoughnessStrength
	u_EmissiveColor_Name
	u_EmissiveColor_Type
	u_EmissiveColor
	u_EmissiveColorR
	u_EmissiveColorG
	u_EmissiveColorB
	u_ScaleIBL_Occl_Name
	u_ScaleIBL_Occl_Type
	u_ScaleIBL_Occl
	u_ScaleIBL_OcclXYZ
	u_ScaleIBL_OcclX
	u_ScaleIBL_OcclY
	u_ScaleIBL_OcclZ
	u_ScaleIBL_OcclW

	*/
	MStatus status;
	const auto shaderObject = shaderNode.object(&status);
	THROW_ON_FAILURE(status);

	// Base color 
	m_glBaseColorFactor = { 1, 1, 1, 1 };
	if (getColor(shaderObject, "u_BaseColorFactor", m_glBaseColorFactor))
	{
		m_glMetallicRoughness.baseColorFactor = &m_glBaseColorFactor[0];
		m_glMaterial.metallicRoughness = &m_glMetallicRoughness;
	}

	GLTF::Texture* baseColorTexture = nullptr;
	if (tryCreateTexture(resources, shaderObject, "u_BaseColorTexture", baseColorTexture))
	{
		m_glBaseColorTexture.texture = baseColorTexture;
		m_glMetallicRoughness.baseColorTexture = &m_glBaseColorTexture;
	}

	// Roughness and metallic 
	m_glMetallicRoughness.roughnessFactor = 0.5f;
	m_glMetallicRoughness.metallicFactor = 0.5f;
	if (getScalar(shaderObject, "u_RoughnessStrength", m_glMetallicRoughness.roughnessFactor) ||
		getScalar(shaderObject, "u_MetallicStrength", m_glMetallicRoughness.metallicFactor))
	{
		m_glMaterial.metallicRoughness = &m_glMetallicRoughness;
	}

	GLTF::Texture* roughnessTexture = nullptr;
	GLTF::Texture* metallicTexture = nullptr;
	if (tryCreateTexture(resources, shaderObject, "u_RoughnessTexture", roughnessTexture) ||
		tryCreateTexture(resources, shaderObject, "u_MetallicTexture", metallicTexture))
	{
		if (roughnessTexture == metallicTexture)
		{
			m_glMetallicRoughnessTexture.texture = roughnessTexture;
			m_glMetallicRoughness.metallicRoughnessTexture = &m_glMetallicRoughnessTexture;
		}
		else
		{
			cerr << prefix << "WARNING: The roughness and metallic texture must use the same file and samplers" << endl;
		}
	}

	// Emissive 
	m_glEmissiveFactor = { 0,0,0,0 };
	if (getColor(shaderObject, "u_EmissiveColor", m_glEmissiveFactor))
	{
		m_glMaterial.emissiveFactor = &m_glEmissiveFactor[0];
	}

	GLTF::Texture* emissiveTexture = nullptr;
	if (tryCreateTexture(resources, shaderObject, "u_EmissiveTexture", emissiveTexture))
	{
		m_glEmissiveTexture.texture = baseColorTexture;
		m_glMaterial.emissiveTexture = &m_glEmissiveTexture;
	}

	// Ambient occlusion
	getScalar(shaderObject, "u_OcclusionStrength", m_glOcclusionTexture.scale);

	GLTF::Texture* occlusionTexture = nullptr;
	if (tryCreateTexture(resources, shaderObject, "u_OcclusionTexture", occlusionTexture))
	{
		m_glOcclusionTexture.texture = occlusionTexture;
		m_glMaterial.occlusionTexture = &m_glOcclusionTexture;
	}

	// Normal
	getScalar(shaderObject, "u_NormalScale", m_glNormalTexture.scale);

	GLTF::Texture* normalTexture = nullptr;
	if (tryCreateTexture(resources, shaderObject, "u_NormalTexture", normalTexture))
	{
		m_glNormalTexture.texture = normalTexture;
		m_glMaterial.normalTexture = &m_glNormalTexture;
	}
}


ExportableMaterialPBR::~ExportableMaterialPBR()
{
}

ExportableDefaultMaterial::ExportableDefaultMaterial()
{
	m_glBaseColorFactor = { 1, 1, 1, 1 };
	m_glMetallicRoughness.baseColorFactor = &m_glBaseColorFactor[0];

	m_glMetallicRoughness.metallicFactor = 0.5f;
	m_glMetallicRoughness.roughnessFactor = 0.5f;
	m_glMaterial.metallicRoughness = &m_glMetallicRoughness;

	m_glEmissiveFactor = { 0.1f, 0.1f, 0.1f };
	m_glMaterial.emissiveFactor = &m_glEmissiveFactor[0];
}

ExportableDefaultMaterial::~ExportableDefaultMaterial()
{
}

ExportableDebugMaterial::ExportableDebugMaterial(const Float3& hsv)
{
	m_glBaseColorFactor = hsvToRgb(hsv, 1);
	m_glMetallicRoughness.baseColorFactor = &m_glBaseColorFactor[0];

	m_glMetallicRoughness.metallicFactor = 0;
	m_glMetallicRoughness.roughnessFactor = 1;
	m_glMaterial.metallicRoughness = &m_glMetallicRoughness;

	m_glEmissiveFactor = { 0, 0, 0 };
	m_glMaterial.emissiveFactor = &m_glEmissiveFactor[0];
}

ExportableDebugMaterial::~ExportableDebugMaterial()
{
}
