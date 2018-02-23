#include "externals.h"
#include "dump.h"
#include "IndentableStream.h"

void dump_array(IndentableStream& out, const std::string& name, const MStringArray& items)
{
	out << quoted(name) << " : [";

	JsonSeparator sep(", ");

	for (unsigned i = 0; i < items.length(); ++i)
	{
		out << sep << std::quoted(items[i].asChar());
	}

	out << "]";
}

