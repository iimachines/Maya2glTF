#include "externals.h"
#include "Arguments.h"
#include "MayaException.h"
#include "IndentableStream.h"

namespace flag
{
	const auto outputFolder = "of";
	const auto sceneName = "sn";
	const auto glb = "glb";
	const auto dumpMaya = "dmy";
	const auto dumpGLTF = "dgl";
	const auto separate = "sep";
	const auto defaultMaterial = "dm";
	const auto colorizeMaterials = "cm";
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

	status = syntax.addFlag(flag::dumpGLTF, "dumpGTLF", MSyntax::MArgType::kString);
	ASSERT_SUCCESS(status);

	status = syntax.addFlag(flag::dumpMaya, "dumpMaya", MSyntax::MArgType::kString);
	ASSERT_SUCCESS(status);

	status = syntax.addFlag(flag::separate, "separate", MSyntax::MArgType::kNoArg);
	ASSERT_SUCCESS(status);

	status = syntax.addFlag(flag::defaultMaterial, "defaultMaterial", MSyntax::MArgType::kNoArg);
	ASSERT_SUCCESS(status);

	status = syntax.addFlag(flag::colorizeMaterials, "colorizeMaterials", MSyntax::MArgType::kNoArg);
	ASSERT_SUCCESS(status);

	syntax.useSelectionAsDefault(true);

	return syntax;
}

Arguments::Arguments(const MArgList& args, const MSyntax& syntax)
{
	MStatus status;
	MArgDatabase adb(syntax, args, &status);

	// TODO: How to provide more error information about what arguments are wrong?
	if (status.error())
		throw MayaException(status, "Invalid arguments");

	status = adb.getObjects(selection);
	if (status.error() || selection.length() < 1)
		throw MayaException(status, "At least one object must be selected or passed to the command");

	if (!adb.isFlagSet(flag::outputFolder))
		throw MayaException(status, "Missing argument -outputFolder");

	status = adb.getFlagArgument(flag::outputFolder, 0, outputFolder);
	THROW_ON_FAILURE(status);

	glb = adb.isFlagSet(flag::glb);

	m_mayaOutputStream = getOutputStream(adb, flag::dumpMaya, "Maya debug", m_mayaOutputFileStream);
	m_gltfOutputStream = getOutputStream(adb, flag::dumpGLTF, "glTF debug", m_gltfOutputFileStream);

	dumpMaya = m_mayaOutputStream.get();
	dumpGLTF = m_gltfOutputStream.get();

	separate = adb.isFlagSet(flag::separate);
	defaultMaterial = adb.isFlagSet(flag::defaultMaterial);
	colorizeMaterials = adb.isFlagSet(flag::colorizeMaterials);

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

	// For debugging, dump the arguments again
	MStringArray selectedObjects;
	status = selection.getSelectionStrings(selectedObjects);
	THROW_ON_FAILURE(status);

	cout << prefix << "Using arguments -sn " << sceneName << " -of " << outputFolder << " " << selectedObjects << endl;
}

Arguments::~Arguments()
{
	if (m_mayaOutputFileStream.is_open())
	{
		m_mayaOutputFileStream.flush();
		m_mayaOutputFileStream.close();
	}

	if (m_gltfOutputFileStream.is_open())
	{
		m_gltfOutputFileStream.flush();
		m_gltfOutputFileStream.close();
	}
}

std::unique_ptr<IndentableStream> Arguments::getOutputStream(const MArgDatabase& adb, const char* arg, const char *outputName, std::ofstream& fileOutputStream)
{
	std::ostream* out = nullptr;

	if (adb.isFlagSet(arg))
	{
		MString path;
		if (adb.getFlagArgument(arg, 0, path).error() || path.toLowerCase() == "console")
		{
			out = &cout;
		}
		else if (path.length() == 0 || path.substring(0, 0) == "-")
		{
			throw MayaException(MStatus::kInvalidParameter, 
				formatted("%s requires an output filepath argument, or just 'console' to print to Maya's console window", arg));
		}
		else
		{
			cout << prefix << "Writing " << outputName << " output to file " << path.asChar() << endl;

			fileOutputStream.open(path.asChar());
			out = &fileOutputStream;
		}
	}

	return out ? move(std::make_unique<IndentableStream>(*out)) : nullptr;
}

