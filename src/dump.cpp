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

std::string escaped(const std::string& s)
{
	std::stringstream ss;

	ss << '"';

	for (std::string::const_iterator i = s.begin(), end = s.end(); i != end; ++i)
	{
		unsigned char c = *i;
		if (' ' <= c && c <= '~' && c != '\\' && c != '"') 
		{
			ss << c;
		}
		else 
		{
			ss << '\\';
			switch (c) {
			case '"':  ss << '"';  break;
			case '\\': ss << '\\'; break;
			case '\t': ss << 't';  break;
			case '\r': ss << 'r';  break;
			case '\n': ss << 'n';  break;
			default:
				char const* const hexdig = "0123456789ABCDEF";
				ss << 'x';
				ss << hexdig[c >> 4];
				ss << hexdig[c & 0xF];
			}
		}
	}

	ss << '"';

	return ss.str();
}
