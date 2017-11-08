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
		cout << "Hello from Maya2glTF" << endl;
		return MStatus::kSuccess;
	}
	catch (const MayaException &ex)
	{
		cerr << ex.what() << endl;
		return ex.status;
	}
	catch (const std::exception &ex)
	{
		cerr << ex.what() << endl;
		return MStatus::kFailure;
	}
	catch (...)
	{
		cerr << "Maya2glTF: unexpected error!" << endl;
		return MStatus::kFailure;
	}
}

bool Maya2glTF::isUndoable() const
{
	return false;
}
