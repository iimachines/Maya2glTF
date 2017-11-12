#include "externals.h"
#include "Exporter.h"
#include "MayaException.h"
#include "Arguments.h"
#include "SignalHandlers.h"
#include "ExportableMesh.h"

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

	std::vector<std::unique_ptr<ExportableItem>> exportables;

	for (uint selectionIndex = 0; selectionIndex < selection.length(); ++selectionIndex)
	{
		MDagPath dagPath;
		THROW_ON_FAILURE(selection.getDagPath(selectionIndex, dagPath));

		MString name = dagPath.partialPathName(&status);
		THROW_ON_FAILURE(status);

		MObject node = dagPath.node(&status);
		if (node.isNull() || status.error())
		{
			cerr << "glTF2Maya: skipping '" << name.asChar() << "' as it is not a node" << endl;
			continue;
		}

		GLTF::Node glNode;

		switch (dagPath.apiType(&status))
		{
		case MFn::kMesh:
			exportables.push_back(std::make_unique<ExportableMesh>(dagPath, glNode));
			break;
		default:
			cerr << "glTF2Maya: skipping '" << name.asChar() << "', it is not supported" << endl;
			break;
		}

		// Generate JSON file
		rapidjson::StringBuffer s;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter = rapidjson::Writer<rapidjson::StringBuffer>(s);
		jsonWriter.StartObject();

		GLTF::Options options;
		glAsset.writeJSON(&jsonWriter, &options);
		jsonWriter.EndObject();

	}


}
