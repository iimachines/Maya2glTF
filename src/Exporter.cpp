#include "externals.h"
#include "Exporter.h"
#include "MayaException.h"
#include "Arguments.h"
#include "SignalHandlers.h"
#include "ExportableMesh.h"
#include "ExportableNode.h"

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

		auto exportableNode = ExportableNode::from(dagPath);

		if (exportableNode)
		{
			glScene.nodes.push_back(&exportableNode->glNode);
			exportables.push_back(std::move(exportableNode));
		}
	}


	glAsset.packAccessors();

	// Generate glTF JSON file
	rapidjson::StringBuffer jsonStringBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonStringBuffer);
	jsonWriter.StartObject();

	GLTF::Options options;
	glAsset.writeJSON(&jsonWriter, &options);
	jsonWriter.EndObject();

	std::string jsonString = jsonStringBuffer.GetString();

	// Pretty format the JSON
	rapidjson::Document jsonDocument;
	jsonDocument.Parse(jsonString.c_str());

	rapidjson::StringBuffer jsonPrettyBuffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonPrettyWriter(jsonPrettyBuffer);
	jsonDocument.Accept(jsonPrettyWriter);

	const auto outputFolder = path(args.outputFolder.asChar());
	create_directories(outputFolder);

	const auto outputFilename = std::string(args.sceneName.asChar()) + ".glTF";
	const auto outputPath = outputFolder / outputFilename;

	const auto prettyString = jsonPrettyBuffer.GetString();
	//cout << prettyString << endl;

	std::ofstream file(outputPath);
	if (file.is_open()) 
	{
		file << prettyString << endl;
		file.close();
	}
	else {
		std::ostringstream ss;
		ss << "Couldn't write glTF to path '";
		ss << outputPath;
		ss << "'";
		throw std::exception(ss.str().c_str());
	}
}
