#include "externals.h"
#include "dump.h"
#include "IndentableStream.h"

void dump_array(IndentableStream& out, const std::string& name, const MStringArray& items)
{
	out << quoted(name) << " : [";

	auto separator = "";

	for (unsigned i = 0; i < items.length(); ++i)
	{
		out << separator << std::quoted(items[i].asChar());
		separator = ", ";
	}

	out << "]";
}

