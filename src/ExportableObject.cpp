#include "externals.h"
#include "Arguments.h"
#include "ExportableObject.h"
#include "ExportableResources.h"
#include "MayaException.h"

ExportableObject::ExportableObject(MObject mObj)
	:obj(mObj)
{
	MStatus status;
	MFnDependencyNode node(mObj, &status);
	THROW_ON_FAILURE(status);

	auto name = node.name(&status);
	THROW_ON_FAILURE(status);

	m_name = name.asChar();
}

ExportableObject::~ExportableObject()
{
}

