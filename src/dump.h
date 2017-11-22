#pragma once

#include "sceneTypes.h"

template<typename ... Args>
std::string formatted(const char* format, Args ... args)
{
	// https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
	const size_t size = snprintf(nullptr, 0, format, args ...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format, args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

template<typename T>
static void dump_iterable(std::ostream& out, const std::string& name, const T& iterable, const std::string& indent, const int itemsPerLine, const size_t precision = 3)
{
	out << std::fixed;

	const auto itemsIndent = indent + '\t';
	const auto newLineIndent = std::string(",\n") + itemsIndent;
	const auto itemSeparator = std::string(",\t");
	const auto noSeparator = std::string("");

	out << indent << quoted(name) << ": [" << endl << itemsIndent;

	const auto* separator = &noSeparator;

	int counter = itemsPerLine;

	for(auto it=iterable.begin(); it!=iterable.end(); ++it)
	{
		out << *separator << std::setprecision(precision) << *it;

		if (--counter <= 0)
		{
			separator = &newLineIndent;
			counter = itemsPerLine;
		}
		else
		{
			separator = &itemSeparator;
		}
	}

	out << endl << indent << "]";
}

template<typename T>
static void dump_table(std::ostream& out, const std::string& name, const std::array<T, Semantic::COUNT>& table, const std::string& indent, const size_t precision = 3)
{
	out << indent << quoted(name) << ": {" << endl;

	const auto subIndent = indent + "\t";

	for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);

		for (auto&& components : table.at(semanticKind))
		{
			dump_iterable(out, Semantic::name(semanticKind), components, subIndent, dimension(semanticKind), precision);
			out << "," << endl;
		}
	}

	out << indent << "}";
}

void dump_array(std::ostream& out, const std::string& name, const MStringArray& items, const std::string& indent);
