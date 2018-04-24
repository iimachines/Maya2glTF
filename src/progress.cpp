#include "externals.h"
#include "progress.h"

void uiSetupProgress(size_t stepCount)
{
	std::stringstream ss;
	ss << "maya2glTF_exportProgressUI(" << stepCount << ");";
	MGlobal::executeCommand(ss.str().c_str());
}

void uiAdvanceProgress(std::string stepName)
{
	std::stringstream ss;
	ss << "maya2glTF_advanceExportProgressUI(" << stepName << ");";
	
	int result = 0;
	MGlobal::executeCommand(ss.str().c_str(), result);
	if (result < 0)
		throw std::runtime_error("Aborted!");
}

