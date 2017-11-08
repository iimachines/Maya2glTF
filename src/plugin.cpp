#include "externals.h"
#include "Maya2glTF.h"

MStatus initializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj, "WonderMedia Maya to glTF 2.0 exporter", "0.0.0", "Any");
	status = plugin.registerCommand("Maya2glTF", Maya2glTF::creator);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus status;
	MFnPlugin plugin(obj);
	status = plugin.deregisterCommand("Maya2glTF");
	CHECK_MSTATUS_AND_RETURN_IT(status);
	return status;
}
