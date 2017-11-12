#include "externals.h"
#include "Exporter.h"
#include "MayaException.h"
#include "Arguments.h"
#include "Mesh.h"
#include "SignalHandlers.h"
#include "MeshDrawable.h"

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
	SignalHandlers signalHandlers;

	try
	{
		std::cout << "maya2glTF: Parsing arguments..." << endl;
		const Arguments arguments(args, syntax());

		std::cout << "maya2glTF: Starting export..." << endl;
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
		return MayaException::printError("maya2glTF: Unexpected fatal error!");
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
	MStatus status;

	auto& selection = args.selection;

	// TODO: Support all kinds of nodes
	std::vector<std::unique_ptr<Mesh>> meshes(selection.length());

	for (uint selectionIndex = 0; selectionIndex < selection.length(); ++selectionIndex)
	{
		MDagPath dagPath;
		THROW_ON_FAILURE(selection.getDagPath(selectionIndex, dagPath));

		MString meshName = dagPath.partialPathName(&status);
		THROW_ON_FAILURE(status);

		const auto meshPtr = new Mesh(dagPath);
		meshes[selectionIndex].reset(meshPtr);
		meshPtr->dump(meshName.asChar(), "");

		cout << endl;

		MeshDrawable drawable(*meshPtr);
		drawable.dump("drawable", "");

		cout << endl;
	}

}

