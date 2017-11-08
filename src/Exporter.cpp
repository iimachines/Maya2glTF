#include "externals.h"
#include "Exporter.h"
#include "MayaException.h"
#include "Arguments.h"

Exporter::Exporter()
{
}

Exporter::~Exporter()
{
}

void* Exporter::createInstance()
{
	return new Exporter();
}

MStatus Exporter::doIt(const MArgList& args)
{
	try
	{
		std::cout << "maya2glTF: parsing arguments..." << endl;
		const Arguments arguments(args, syntax());

		std::cout << "maya2glTF: starting export..." << endl;
		exportScene(arguments);

		return MStatus::kSuccess;
	}
	catch (const MayaException &ex)
	{
		return MayaException::printError(ex.what(),ex.status);
	}
	catch (const std::exception &ex)
	{
		return MayaException::printError(ex.what());
	}
	catch (...)
	{
		return MayaException::printError("maya2glTF: unexpected fatal error!");
	}
}

bool Exporter::isUndoable() const
{
	return false;
}

bool Exporter::hasSyntax() const
{
	return true;
}

void Exporter::exportScene(const Arguments& args)
{
}

