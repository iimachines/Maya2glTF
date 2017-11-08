#include "externals.h"
#include "Exporter.h"
#include "Arguments.h"
#include "OutputStreamsPatch.h"

#if _DEBUG
static OutputStreamsPatch<char> patch;
#endif

MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj, "WonderMedia Maya to glTF 2.0 exporter", "0.0.0", "Any");
	status = plugin.registerCommand("maya2glTF", Exporter::createInstance, Arguments::createSyntax);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj);
	status = plugin.deregisterCommand("maya2glTF");
	CHECK_MSTATUS_AND_RETURN_IT(status);
	return status;
}
