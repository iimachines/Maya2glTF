#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <signal.h>
#endif

	/** Overrides calls to abort to throw an exception instead of killing the process */
	class SignalHandlers
	{
	public:
		SignalHandlers();
		~SignalHandlers();

	private:
		
#if defined(_WIN32) || defined(_WIN64)
		_crt_signal_t m_previousAbortSignalHandler;
#else
		__sighandler_t m_previousAbortSignalHandler;
#endif

		static void handleAbortSignal(int signalNumber);
	};
