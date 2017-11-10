#include "externals.h"
#include "dump.h"

void dump_array(const std::string name, MStringArray items, const std::string indent)
{
	cout << indent << name << ": [ ";

	auto separator = "";

	for (unsigned i = 0; i<items.length(); ++i)
	{
		cout << separator;
		cout << items[i];
		separator = ", ";
	}
}

