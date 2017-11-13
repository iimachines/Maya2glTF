#pragma once
#include <signal.h>

class MayaException : public std::runtime_error
{
public:
	MayaException(const MStatus error, const std::string& message) : runtime_error("maya2glTF: " + message), status(error)
	{
	}

	const MStatus status;

	/** Formats an error message and throws me */
	static void throwIt(const MStatus status, const char* file, int line, const char* function);

	/** Prints an error to the standard error and the Maya script window */
	static MStatus printError(const char* message, MStatus error = MStatus::kFailure);
};


#define ASSERT_SUCCESS(__expression__) \
	assert(MStatus::kSuccess == (__expression__));

#define THROW_ON_FAILURE(__expression__) { \
	MStatus __status__ = (__expression__); \
	ASSERT_SUCCESS(__status__); \
	if (MStatus::kSuccess != __status__) \
		MayaException::throwIt(__status__, __FILE__, __LINE__, __FUNCTION__); \
}
