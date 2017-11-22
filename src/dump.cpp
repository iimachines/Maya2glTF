#include "externals.h"
#include "dump.h"

void dump_array(std::ostream& out, const std::string& name, const MStringArray& items, const std::string& indent)
{
	out << indent << quoted(name) << " : [";

	auto separator = "";

	for (unsigned i = 0; i < items.length(); ++i)
	{
		out << separator << std::quoted(items[i].asChar());
		separator = ", ";
	}

	out << "]";
}

