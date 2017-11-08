#include "externals.h"
#include "MayaException.h"

void MayaException::throwIt(const MStatus status, const char* file, const int line, const char* function)
{
	std::stringstream err;
	err << "Maya2glTF error '" << status.errorString().asChar() << "' in " << function << " (" << file << ":" << line << ")";
	throw MayaException(status, err.str());
}
