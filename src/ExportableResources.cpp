#include "externals.h"
#include "ExportableResources.h"
#include "DagHelper.h"
#include "MayaException.h"
#include "ExportableMaterial.h"
#include "Mesh.h"
#include "ExportableMesh.h"

ExportableResources::ExportableResources(const bool dumpMayaMesh)
	:m_dumpMayaMesh(dumpMayaMesh)
{
}


ExportableResources::~ExportableResources()
{
}

ExportableMaterial* ExportableResources::getMaterial(const MObject& shaderGroup)
{
	MStatus status;

	MObject surfaceShader = DagHelper::findSourceNodeConnectedTo(shaderGroup, "surfaceShader");

	if (surfaceShader.isNull())
		return nullptr;

	MFnDependencyNode shaderNode(surfaceShader, &status);

	MString mayaName = shaderNode.absoluteName(&status);
	THROW_ON_FAILURE(status);

	const std::string key(mayaName.asChar());

	auto& materialPtr = materialMap[key];
	if (materialPtr)
	{
		cout << "maya2glTF: Reusing material instance " <<key << endl;
	}
	else
	{
		// Create new material.
		materialPtr = ExportableMaterial::from(*this, shaderNode);
	}

	return materialPtr.get();
}
