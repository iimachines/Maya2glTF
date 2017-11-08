#include "externals.h"
#include "Maya2glTF.h"
#include "MayaException.h"

Maya2glTF::Maya2glTF()
{
}

Maya2glTF::~Maya2glTF()
{
}

void* Maya2glTF::creator()
{
	return new Maya2glTF();
}

MStatus Maya2glTF::doIt(const MArgList& args)
{
	try
	{
		THROW_ON_FAILURE(MStatus::kInsufficientMemory);

		cout << "Hello from Maya2glTF" << endl;
		return MStatus::kSuccess;
	}
	catch (const MayaException &ex)
	{
		return fail(ex.what(),ex.status);
	}
	catch (const std::exception &ex)
	{
		return fail(ex.what());
	}
	catch (...)
	{
		return fail("Maya2glTF: unexpected fatal error!");
	}
}

bool Maya2glTF::isUndoable() const
{
	return false;
}

MStatus Maya2glTF::fail(const char* message, MStatus status) const
{
	MGlobal::executeCommand(MString("error \"") + message + "\"");
	cerr << message << endl;
	return status;
}

