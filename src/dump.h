#pragma once

#include "SceneTypes.h"

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
static void dump_table(const std::string& name, const T& table, const std::string& indent, const size_t precision = 3)
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
