#include "externals.h"
#include "Exporter.h"
#include "MayaException.h"
#include "Arguments.h"
#include "SignalHandlers.h"
#include "ExportableMesh.h"
#include "ExportableNode.h"
#include "ExportableAsset.h"
#include "ExportableResources.h"

typedef void(*SignalHandlerPointer)(int);

void SignalHandler(int signal)
{
	MayaException::printError("An Access Violation occurred! Please save your work to a new file since data might have been corrupted!");
	assert(false);
}

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
	const auto previousHandler = signal(SIGSEGV, SignalHandler);
	auto status = run(args);
	signal(SIGSEGV, previousHandler);
	return status;
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
	ExportableAsset exportableAsset(args);
	exportableAsset.save();
}

MStatus Exporter::run(const MArgList& args)
{
	try
	{
		std::cout << prefix << "Parsing arguments..." << endl;
		const Arguments arguments(args, syntax());

		std::cout << prefix << "Starting export..." << endl;
		exportScene(arguments);

		std::cout << prefix << "Finished export :-)" << endl;

		return MStatus::kSuccess;
	}
	catch (const MayaException &ex)
	{
		return MayaException::printError(ex.what(), ex.status);
	}
	catch (const std::exception &ex)
	{
		return MayaException::printError(ex.what());
	}
	catch (...)
	{
		return MayaException::printError("Unexpected fatal error!");
	}
}
