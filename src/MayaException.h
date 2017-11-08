#pragma once

class MayaException : public std::runtime_error
{
public:
	MayaException(const MStatus error, const std::string& message) : runtime_error(message), status(error)
	{
	}

	const MStatus status;

	static void throwIt(const MStatus status, const char* file, int line, const char* function);
};

#define THROW_ON_FAILURE(expression) { \
	MStatus status = (expression); \
	if (MStatus::kSuccess != status) \
		MayaException::throwIt(status, __FILE__, __LINE__, __FUNCTION__); \
}

