#include "externals.h"
#include "Arguments.h"
#include "MayaException.h"
#include <fstream>

namespace flag
{
	const auto outputFolder = "of";
	const auto sceneName = "sn";
	const auto glb = "glb";
	const auto print = "pr";
	const auto separate = "sep";
}

MSyntax Arguments::createSyntax()
{
	MStatus status;
	MSyntax syntax;

	status = syntax.setObjectType(MSyntax::MObjectFormat::kSelectionList, 1);
	ASSERT_SUCCESS(status);

	status = syntax.addFlag(flag::outputFolder, "outputFolder", MSyntax::MArgType::kString);
	ASSERT_SUCCESS(status);

	status = syntax.addFlag(flag::sceneName, "sceneName", MSyntax::MArgType::kString);
	ASSERT_SUCCESS(status);

	status = syntax.addFlag(flag::glb, "binary", MSyntax::MArgType::kNoArg);
	ASSERT_SUCCESS(status);

	status = syntax.addFlag(flag::print, "print", MSyntax::MArgType::kNoArg);
	ASSERT_SUCCESS(status);

	status = syntax.addFlag(flag::separate, "separate", MSyntax::MArgType::kNoArg);
	ASSERT_SUCCESS(status);

	syntax.useSelectionAsDefault(true);

	return syntax;
}

Arguments::Arguments(const MArgList& args, const MSyntax& syntax)
{
	MStatus status;
	MArgDatabase adb(syntax, args, &status);
	THROW_ON_FAILURE(status);

	status = adb.getObjects(selection);
	if (status.error() || selection.length() < 1)
		throw MayaException(status, "At least one object must be selected or passed to the command");

	if (!adb.isFlagSet(flag::outputFolder))
		throw MayaException(status, "Missing argument -outputFolder");

	status = adb.getFlagArgument(flag::outputFolder, 0, outputFolder);
	THROW_ON_FAILURE(status);

	glb = adb.isFlagSet(flag::glb);
	print = adb.isFlagSet(flag::print);
	separate = adb.isFlagSet(flag::separate);

	if (adb.isFlagSet(flag::sceneName))
	{
		status = adb.getFlagArgument(flag::sceneName, 0, sceneName);
		THROW_ON_FAILURE(status);
	}
	else
	{
		// Use filename without extension of current scene file.
		MFileIO fileIO;
		const auto currentFilePath = fileIO.currentFile();
		
		MFileObject fileObj;
		fileObj.setFullName(currentFilePath);

		// Remove extension from filename. I really miss C#!
		std::string fileName(fileObj.name().asChar());

		const auto lastindex = fileName.find_last_of(".");
		sceneName = fileName.substr(0, lastindex).c_str();
	}

	// For debugging, print the arguments again
	MStringArray selectedObjects;
	status = selection.getSelectionStrings(selectedObjects);
	THROW_ON_FAILURE(status);

	cout << "maya2glTF: Using arguments -sn " << sceneName << " -of " << outputFolder << " " << selectedObjects << endl;
}

Arguments::~Arguments()
{
}

