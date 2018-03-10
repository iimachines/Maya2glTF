#pragma once

#include "sceneTypes.h"
#include "IndentableStream.h"

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
static void dump_iterable(std::ostream& out, const std::string& name, const T& iterable, const size_t itemsPerLine, const size_t precision = 3)
{
	out << std::fixed;

	const auto itemsIndent = '\t';
	const auto newLineIndent = std::string(",\n") + itemsIndent;
	const auto itemSeparator = std::string(",\t");
	const auto noSeparator = std::string("");

	out << quoted(name) << ": [" << endl << itemsIndent;

	const auto* separator = &noSeparator;

	int counter = static_cast<int>(itemsPerLine);

	for(auto it=iterable.begin(); it!=iterable.end(); ++it)
	{
		const auto& val = *it;

		out << *separator << std::setprecision(precision) << val;

		if (--counter <= 0)
		{
			separator = &newLineIndent;
			counter = static_cast<int>(itemsPerLine);
		}
		else
		{
			separator = &itemSeparator;
		}
	}

	out << endl << "]";
}

template<typename T>
static void dump_index_table(std::ostream& out, const std::string& name, const std::array<T, Semantic::COUNT>& table, const size_t indicesPerPrimitive, const size_t precision = 3)
{
	out << quoted(name) << ": {" << endl << indent;

	JsonSeparator sep(",\n");

	for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);

		for (auto&& components : table.at(semanticKind))
		{
			out << sep;
			dump_iterable(out, Semantic::name(semanticKind), components, indicesPerPrimitive, precision);
		}
	}

	out << endl << undent << "}";
}

template<typename T>
static void dump_vertex_table(std::ostream& out, const std::string& name, const std::array<T, Semantic::COUNT>& table, const int shapeIndex, const size_t precision = 3)
{
	out << quoted(name) << ": {" << endl << indent;

	out << "\"shapeIndex\": " << shapeIndex << ", " << endl;

	JsonSeparator sep(",\n");

	for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);

		for (auto&& components : table.at(semanticKind))
		{
			out << sep;
			dump_iterable(out, Semantic::name(semanticKind), components, dimension(semanticKind, shapeIndex), precision);
		}
	}

	out << endl << undent << "}";

}

void dump_array(std::ostream& out, const std::string& name, const MStringArray& items);

std::string escaped(const std::string& s);
