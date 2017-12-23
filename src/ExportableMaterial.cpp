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
	if (shaderNode.typeName() == "StingrayPBS" || resources.arguments().forcePbrMaterials)
		return std::make_unique<ExportableMaterialPBR>(resources, shaderNode);

	cerr << "maya2GLTF: unsupported shader node type: " << std::setw(24) << shaderNode.typeName().asChar() << endl;

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

	auto apiType = fileTextureObj.apiType();
	cout << "API type = " << apiType << endl;
	if (apiType != MFn::kFileTexture)
		return false;

	MString filename;
	if (!DagHelper::getPlugValue(fileTextureObj, "fileTextureName", filename))
		return false;

	cout << prefix << "Found texture '" << filename << "'" << endl;

	int filterType = IMAGE_FILTER_MipMap;
	DagHelper::getPlugValue(fileTextureObj, "filterType", filterType);
	cout << prefix << "filter type = " << filterType << endl;

	int uWrap = false;
	int vWrap = false;
	int uMirror = false;
	int vMirror = false;

	DagHelper::getPlugValue(fileTextureObj, "wrapU", uWrap);
	DagHelper::getPlugValue(fileTextureObj, "wrapV", vWrap);
	DagHelper::getPlugValue(fileTextureObj, "mirrorU", uMirror);
	DagHelper::getPlugValue(fileTextureObj, "mirrorV", vMirror);

	cout << prefix << "image wrapping = " << uWrap << " " << vWrap << ", mirror = " << uMirror << " " << vMirror << endl;

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

bool ExportableMaterial::getScalar(const MObject& shaderObject, const char* attributeName, float& scalar)
{
	return DagHelper::getPlugValue(shaderObject, attributeName, scalar);
}

bool ExportableMaterial::getColor(const MObject& shaderObject, const char* attributeName, Float4& color)
{
	MColor c;
	if (!DagHelper::getPlugValue(shaderObject, attributeName, c))
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

	cout << prefix << "shader type = " << shaderType << endl;

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
	default:
		loadPBR(resources, shaderObject);
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
}



void ExportableMaterialPBR::loadPBR(ExportableResources& resources, const MFnDependencyNode& shaderNode)
{
	MStatus status;
	const auto shaderObject = shaderNode.object(&status);
	THROW_ON_FAILURE(status);

	// Copy base color factors
	m_glBaseColorFactor = { 1, 1, 1, 1 };
	if (getColor(shaderObject, "base_color", m_glBaseColorFactor))
	{
		m_glMetallicRoughness.baseColorFactor = &m_glBaseColorFactor[0];
		m_glMaterial.metallicRoughness = &m_glMetallicRoughness;
	}

	// Copy roughness and metallic factors
	m_glMetallicRoughness.roughnessFactor = 0.5f;
	m_glMetallicRoughness.metallicFactor = 0.5f;
	if (getScalar(shaderObject, "roughness", m_glMetallicRoughness.roughnessFactor) ||
		getScalar(shaderObject, "metallic", m_glMetallicRoughness.metallicFactor))
	{
		m_glMaterial.metallicRoughness = &m_glMetallicRoughness;
	}

	// Copy emissive color factors
	Float4 emissiveColor = { 0,0,0,0 };
	float emissiveScale = 1;
	if (getColor(shaderObject, "emissive", emissiveColor) ||
		getScalar(shaderObject, "emissive_intensity", emissiveScale))
	{
		m_glEmissiveFactor =
		{
			emissiveColor[0] * emissiveScale,
			emissiveColor[1] * emissiveScale,
			emissiveColor[2] * emissiveScale,
		};

		m_glMaterial.emissiveFactor = &m_glEmissiveFactor[0];
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
