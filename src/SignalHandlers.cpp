#include "externals.h"
#include "SignalHandlers.h"

SignalHandlers::SignalHandlers()
{
	m_previousAbortSignalHandler = signal(SIGABRT, handleAbortSignal);
}

SignalHandlers::~SignalHandlers()
{
	signal(SIGABRT, m_previousAbortSignalHandler);
}

void SignalHandlers::handleAbortSignal(int signalNumber)
{
	throw std::runtime_error("the operation was aborted unexpectedly");
}

