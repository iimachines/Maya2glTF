#include "externals.h"
#include "ExportableMaterial.h"
#include "DagHelper.h"
#include "MayaException.h"

ExportableMaterial::~ExportableMaterial()
{
}

std::unique_ptr<ExportableMaterial> ExportableMaterial::from(ExportableResources& resources, const MFnDependencyNode& shaderNode)
{
	if (shaderNode.typeName() == "StingrayPBS")
		return std::make_unique<ExportableMaterialPBR>(resources, shaderNode);

	cerr << "maya2GLTF: unsupported shader node type: " << std::setw(24) << shaderNode.typeName().asChar() << endl;

	return nullptr;
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

	// Copy base color factors
	m_pbrBaseColorFactor = { 1, 1, 1, 1 };
	if (getColor(shaderObject, "base_color", m_pbrBaseColorFactor))
	{
		m_pbrMetallicRoughness.baseColorFactor = &m_pbrBaseColorFactor[0];
	}

	// Copy roughness and metallic factors
	if (getScalar(shaderObject, "roughness", m_pbrMetallicRoughness.roughnessFactor) |
		getScalar(shaderObject, "metallic", m_pbrMetallicRoughness.metallicFactor))
	{
		m_pbrMaterial.metallicRoughness = &m_pbrMetallicRoughness;
	}

	// Copy emissive color factors
	m_pbrEmissiveFactor = { 0,0,0 };
	Float4 emissiveColor;
	float emissiveScale;
	if (getColor(shaderObject, "emissive", emissiveColor) &&
		getScalar(shaderObject, "emissive_intensity", emissiveScale))
	{
		m_pbrEmissiveFactor =
		{
			emissiveColor[0] * emissiveScale,
			emissiveColor[1] * emissiveScale,
			emissiveColor[2] * emissiveScale,
		};

		m_pbrMaterial.emissiveFactor = &m_pbrEmissiveFactor[0];
	}

	// TODO: Copy texture maps
	return;

	// Dump attributes for debugging.
	const auto attributeCount = shaderNode.attributeCount(&status);
	THROW_ON_FAILURE(status);

	for (unsigned attributeIndex = 0; attributeIndex < attributeCount; attributeIndex++)
	{
		MObject attribute = shaderNode.attribute(attributeIndex, &status);
		THROW_ON_FAILURE(status);

		MFnAttribute attributeFn(attribute, &status);
		THROW_ON_FAILURE(status);

		MString name = attributeFn.name(&status);
		THROW_ON_FAILURE(status);

		MPlug plug = shaderNode.findPlug(attribute);
		MObject obj;
		plug.getValue(obj);

		MObject connectedNode = DagHelper::findNodeConnectedTo(plug);

		cout << "attr: " << std::setw(24) << name.asChar()
			<< " type: " << std::setw(18) << obj.apiTypeStr();

		if (!connectedNode.isNull())
		{
			cout << " connected to type: " << std::setw(18) << connectedNode.apiTypeStr();

			if (connectedNode.apiType() == MFn::kFileTexture)
			{
				MString filename;
				DagHelper::getPlugValue(connectedNode, "fileTextureName", filename);
				cout << " texture filename: " << filename;
			}
		}

		cout << endl;
		cout.flush();
	}


}

ExportableMaterialPBR::~ExportableMaterialPBR()
{
}

ExportableDefaultMaterial::ExportableDefaultMaterial()
{
	m_pbrBaseColorFactor = { 1, 1, 1, 1 };
	m_pbrMetallicRoughness.baseColorFactor = &m_pbrBaseColorFactor[0];

	m_pbrMetallicRoughness.metallicFactor = 0.5f;
	m_pbrMetallicRoughness.roughnessFactor = 0.5f;
	m_pbrMaterial.metallicRoughness = &m_pbrMetallicRoughness;

	m_pbrEmissiveFactor = { 0.1f, 0.1f, 0.1f };
	m_pbrMaterial.emissiveFactor = &m_pbrEmissiveFactor[0];
}

ExportableDefaultMaterial::~ExportableDefaultMaterial()
{
}

ExportableDebugMaterial::ExportableDebugMaterial(const Float3& hsv)
{
	m_pbrBaseColorFactor = hsvToRgb(hsv, 1);
	m_pbrMetallicRoughness.baseColorFactor = &m_pbrBaseColorFactor[0];

	m_pbrMetallicRoughness.metallicFactor = 0;
	m_pbrMetallicRoughness.roughnessFactor = 1;
	m_pbrMaterial.metallicRoughness = &m_pbrMetallicRoughness;

	m_pbrEmissiveFactor = { 0, 0, 0 };
	m_pbrMaterial.emissiveFactor = &m_pbrEmissiveFactor[0];
}

ExportableDebugMaterial::~ExportableDebugMaterial()
{
}
