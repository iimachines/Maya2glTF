#include "externals.h"
#include "filepath.h"

path generateTempPath(const path extension)
{
	MUuid tempId;
	tempId.generate();

	const path tempFolderPath = temp_directory_path();
	path tempFileName(tempId.asString().asChar());
	tempFileName.replace_extension(extension);

	path tempFilePath = tempFolderPath / tempFileName;

	return tempFilePath;
}
