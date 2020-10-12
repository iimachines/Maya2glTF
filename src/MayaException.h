#pragma once
#include "dump.h"

class MayaException : public std::runtime_error {
  public:
    MayaException(const MStatus error, const std::string &message) : runtime_error(message), status(error) {}

    const MStatus status;

    /** Formats an error message and throws me */
    static void throwIt(const MStatus status, const std::string &message, const char *file, int line,
                        const char *function);

    /** Prints an error to the standard error and the Maya script window */
    static MStatus printError(const std::string &message, const MStatus &error);

    /** Prints an error to the standard error and the Maya script window */
    static void printError(const std::string &message);

    /** Prints an warning to the standard error and the Maya script window */
    static MStatus printWarning(const std::string &message, const MStatus &error);

    /** Prints an warning to the standard error and the Maya script window */
    static void printWarning(const std::string &message);
};

#ifdef _DEBUG
#define DEBUG_ASSERT_SUCCESS(__expression__) assert(MStatus::kSuccess == (__expression__));
#else
#define DEBUG_ASSERT_SUCCESS(__expression__)
#endif

#define THROW_ON_FAILURE(__expression__)                                                                               \
    {                                                                                                                  \
        const MStatus __status__ = (__expression__); /* NOLINT */                                                      \
        DEBUG_ASSERT_SUCCESS(__status__);                                                                              \
        if (MStatus::kSuccess != __status__)                                                                           \
            MayaException::throwIt(__status__, "", __FILE__, __LINE__, __FUNCTION__);                                  \
    }

#define RETURN_ON_FAILURE(__expression__)                                                                              \
    {                                                                                                                  \
        const MStatus __status__ = (__expression__); /* NOLINT */                                                      \
        if (MStatus::kSuccess != __status__)                                                                           \
            return __status__;                                                                                         \
    }

#define THROW_ON_FAILURE_WITH(__expression__, __message__)                                                             \
    {                                                                                                                  \
        const MStatus __status__ = (__expression__); /* NOLINT */                                                      \
        DEBUG_ASSERT_SUCCESS(__status__);                                                                              \
        if (MStatus::kSuccess != __status__)                                                                           \
            MayaException::throwIt(__status__, (__message__), __FILE__, __LINE__, __FUNCTION__);                       \
    }

template <typename... Args> bool checkAndReportStatus(const MStatus &status, const char *format, Args... args) {
    if (status == MStatus::kSuccess)
        return true;

    cerr << prefix << "WARNING: " << formatted(format, args...) << endl;
    return false;
}
