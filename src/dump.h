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
static void dump_iterable(const std::string& name, const T& iterable, const std::string& indent, const size_t precision = 3)
{
	cout << std::fixed;

	cout << indent << quoted(name) << ":\t[";

	auto separator = "";

	for(auto it=iterable.begin(); it!=iterable.end(); ++it)
	{
		cout << separator << std::setprecision(precision) << *it;
		separator = ", ";
	}

	cout << "]";
}

template<typename T>
static void dump_table(const std::string& name, const std::array<T, Semantic::COUNT>& table, const std::string& indent, const size_t precision = 3)
{
	cout << indent << quoted(name) << ": {" << endl;

	const auto subIndent = indent + "\t";

	for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);

		for (auto&& components : table.at(semanticKind))
		{
			dump_iterable(Semantic::name(semanticKind), components, subIndent, precision);
			cout << "," << endl;
		}
	}

	cout << indent << "}";
}

void dump_array(const std::string& name, const MStringArray& items, const std::string& indent);
