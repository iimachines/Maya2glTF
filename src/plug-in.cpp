#include "externals.h"

DeclareSimpleCommand(Maya2glTF, "http://wondermediagroup.net", "2017");

MStatus Maya2glTF::doIt(const MArgList&)
{
	std::cout << "Hello from glTF\n" << std::endl;
	return MS::kSuccess;
}