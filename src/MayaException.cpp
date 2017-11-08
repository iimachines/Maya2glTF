#include "externals.h"
#include "MayaException.h"

void MayaException::throwIt(const MStatus status, const char* file, const int line, const char* function)
{
	std::stringstream err;
	std::string path(file);
	std::replace(path.begin(), path.end(), '\\', '/');
	err << "error '" << status.errorString().asChar() << "' in " << function << " (" << path << ":" << line << ")";
	throw MayaException(status, err.str());
}

MStatus MayaException::printError(const char* message, MStatus status)
{
	MGlobal::executeCommand(MString("error \"") + message + "\"");
	cerr << message << endl;
	return status;
}
