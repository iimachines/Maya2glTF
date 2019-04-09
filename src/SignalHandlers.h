#pragma once

#ifndef _WIN32
typedef void (*_crt_signal_t) (int);
#endif

/** Overrides calls to abort to throw an exception instead of killing the process */
class SignalHandlers
{
public:
	SignalHandlers();
	~SignalHandlers();

private:
	_crt_signal_t m_previousAbortSignalHandler;
	
	static void handleAbortSignal(int signalNumber);
};

