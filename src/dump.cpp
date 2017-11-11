#include "externals.h"
#include "dump.h"

void dump_array(const std::string& name, const MStringArray& items, const std::string& indent)
{
	cout << indent << quoted(name) << " : [";

	auto separator = "";

	for (unsigned i = 0; i < items.length(); ++i)
	{
		cout << separator << std::quoted(items[i].asChar());
		separator = ", ";
	}

	cout << "]";
}

