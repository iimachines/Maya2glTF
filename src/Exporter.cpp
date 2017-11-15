#include "externals.h"
#include "Exporter.h"
#include "MayaException.h"
#include "Arguments.h"
#include "SignalHandlers.h"
#include "ExportableMesh.h"
#include "ExportableNode.h"
#include "ExportableAsset.h"
#include "ExportableResources.h"

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
		return MayaException::printError(ex.what(), ex.status);
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

	GLTF::Asset glAsset;
	GLTF::Scene glScene;

	glAsset.scenes.push_back(&glScene);
	glAsset.scene = 0;

	ExportableResources resources;

	std::vector<std::unique_ptr<ExportableItem>> exportables;

	for (uint selectionIndex = 0; selectionIndex < selection.length(); ++selectionIndex)
	{
		MDagPath dagPath;
		THROW_ON_FAILURE(selection.getDagPath(selectionIndex, dagPath));

		auto exportableNode = ExportableNode::from(dagPath, resources, args);

		if (exportableNode)
		{
			glScene.nodes.push_back(&exportableNode->glNode);
			exportables.push_back(std::move(exportableNode));
		}
	}

	ExportableAsset exportableAsset(glAsset, args);

	if (args.dumpGLTF)
	{
		cout << "glTF dump:" << endl;
		cout << exportableAsset.prettyJsonString();
		cout << endl;
	}
}
