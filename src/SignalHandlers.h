#pragma once
#include <signal.h>

/** Overrides calls to abort to throw an exception instead of killing the process */
class SignalHandlers
{
public:
	SignalHandlers();
	~SignalHandlers();

private:
	__sighandler_t m_previousAbortSignalHandler;
	
	static void handleAbortSignal(int signalNumber);
};

