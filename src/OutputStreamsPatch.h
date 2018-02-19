#pragma once

#include "IndentableStream.h"

/*
 * Workaround for plugin not printing to cout/cerr in debug builds
 * https://forums.autodesk.com/t5/maya-programming/c-api-not-printing-to-output-window/td-p/4260798
 */
template<typename TChar = char>
class OutputStreamsPatch
{
public:
	OutputStreamsPatch()
	{
		original_cout_buf = cout.rdbuf(MStreamUtils::stdOutStream().rdbuf());
		original_cerr_buf = cerr.rdbuf(MStreamUtils::stdErrorStream().rdbuf());
		cout << prefix << "Patched cout and cerr!" << endl;
	}

	~OutputStreamsPatch()
	{
		cout << prefix << "Restoring cout and cerr..." << endl;
		cout.rdbuf(original_cout_buf);
		cerr.rdbuf(original_cout_buf);
	}

private:
	std::basic_streambuf<TChar>* original_cout_buf;
	std::basic_streambuf<TChar>* original_cerr_buf;
};


