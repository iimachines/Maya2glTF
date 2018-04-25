#include "externals.h"
#include "progress.h"
#include "dump.h"

void uiSetupProgress(size_t stepCount)
{
	MGlobal::executeCommand(formatted("maya2glTF_exportProgressUI(%d);", stepCount).c_str());
}

void uiAdvanceProgress(const std::string& stepName)
{
	int result = 0;
	MGlobal::executeCommand(formatted("maya2glTF_advanceExportProgressUI(\"%s\");", stepName.c_str()).c_str(), result);
	if (result < 0)
		throw std::runtime_error("Aborted!");
}

