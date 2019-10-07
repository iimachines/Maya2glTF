#pragma once

/** Overrides calls to abort to throw an exception instead of killing the
 * process */
class SignalHandlers {
  public:
    SignalHandlers();
    ~SignalHandlers();

  private:
#ifdef _WIN32
    _crt_signal_t m_previousAbortSignalHandler;
#else 
    __sighandler_t m_previousAbortSignalHandler;
#endif
    static void handleAbortSignal(int signalNumber);
};
