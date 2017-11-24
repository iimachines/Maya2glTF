#include "externals.h"
#include "ExportableResources.h"
#include "DagHelper.h"
#include "MayaException.h"
#include "ExportableMaterial.h"

ExportableResources::ExportableResources(const Arguments& args)
	:m_args(args)
{
}


ExportableResources::~ExportableResources()
{
}

ExportableMaterial* ExportableResources::getMaterial(const MObject& shaderGroup) 
{
	MStatus status;

	if (shaderGroup.isNull())
		return nullptr;

	MObject surfaceShader = DagHelper::findSourceNodeConnectedTo(shaderGroup, "surfaceShader");

	if (surfaceShader.isNull())
		return nullptr;

	MFnDependencyNode shaderNode(surfaceShader, &status);

	MString mayaName = shaderNode.absoluteName(&status);
	THROW_ON_FAILURE(status);

	const std::string key(mayaName.asChar());

	auto& materialPtr = m_materialMap[key];
	if (materialPtr)
	{
		cout << prefix << "Reusing material instance " <<key << endl;
	}
	else
	{
		// Create new material.
		materialPtr = ExportableMaterial::from(*this, shaderNode);
	}

	return materialPtr.get();
}

ExportableMaterial* ExportableResources::getDebugMaterial(const Float3& hsv)
{
	auto& materialPtr = m_debugMaterialMap[hsv];
	if (!materialPtr)
	{
		materialPtr = std::make_unique<ExportableDebugMaterial>(hsv);
	}

	return materialPtr.get();
}
