#include "externals.h"
#include "ExportableTexture.h"
#include "DagHelper.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "Arguments.h"

ExportableTexture::ExportableTexture(ExportableResources& resources, const MObject& obj, const char* attributeName)
	: glTexture(nullptr)
	, glSampler(nullptr)
{
    if (resources.arguments().skipMaterialTextures)
        return;

	connectedObject = DagHelper::findNodeConnectedTo(obj, attributeName);
	if (connectedObject.isNull())
		return;

	MStatus status;
	MFnDependencyNode connectedNode(connectedObject, &status);
	THROW_ON_FAILURE(status);

	const auto apiType = connectedObject.apiType();
	if (apiType != MFn::kFileTexture)
	{
		MayaException::printError(formatted(
			"Unsupported texture node '%s' #%d",
			connectedObject.apiTypeStr(), apiType));
		return;
	}

	if (!DagHelper::getPlugValue(connectedObject, "fileTextureName", imageFilePath))
	{
		MayaException::printError(
			formatted("Failed to get %s.fileTextureName", connectedNode.name()));
		return;
	}

	int filterType = IMAGE_FILTER_MipMap;
	DagHelper::getPlugValue(connectedObject, "filterType", filterType);

	int uWrap = false;
	int vWrap = false;
	int uMirror = false;
	int vMirror = false;

	DagHelper::getPlugValue(connectedObject, "wrapU", uWrap);
	DagHelper::getPlugValue(connectedObject, "wrapV", vWrap);
	DagHelper::getPlugValue(connectedObject, "mirrorU", uMirror);
	DagHelper::getPlugValue(connectedObject, "mirrorV", vMirror);

	cout << prefix << "Found texture '" << imageFilePath << "'"
		<< " with filter type = " << filterType
		<< ", image wrapping = " << uWrap << " " << vWrap << ", mirror = " << uMirror << " " << vMirror << endl;

	auto uTiling = uWrap * IMAGE_TILING_Wrap + uMirror * IMAGE_TILING_Mirror;
	auto vTiling = vWrap * IMAGE_TILING_Wrap + vMirror * IMAGE_TILING_Mirror;

	glSampler = resources.getSampler(
		static_cast<ImageFilterKind>(filterType),
		static_cast<ImageTilingFlags>(uTiling),
		static_cast<ImageTilingFlags>(vTiling));
	assert(glSampler);

	const auto imagePtr = resources.getImage(imageFilePath.asChar());
	if (!imagePtr)
		return;

	glTexture = resources.getTexture(imagePtr, glSampler);
	assert(glTexture);
}

ExportableTexture::~ExportableTexture() = default;
