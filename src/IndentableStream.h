#pragma once

#include "externals.h"

/** Prints the common prefix ("maya2glTF@<time>: ") */
ostream& prefix(ostream& stream);

class JsonSeparator
{
public:
	JsonSeparator(const char* text) :m_text(text), m_current("")
	{
	}

	friend ostream& operator<<(ostream& os, JsonSeparator& sep)
	{
		os << sep.m_current;
		sep.m_current = sep.m_text;
		return os;
	}

private:
	const char* m_text;
	const char* m_current;
};

class IndentationBuffer : public std::streambuf
{
public:
	IndentationBuffer(std::streambuf* sbuf);

	int indentationLevel() const { return m_indentationLevel; }

	void indent() { ++m_indentationLevel; }

	void undent() { m_indentationLevel = std::max(0, m_indentationLevel - 1); }

protected:

	int_type overflow(const int_type c) override;

	std::streambuf* m_streamBuffer;
	int m_indentationLevel;
	bool m_shouldIndent;
};

class IndentableStream : public ostream
{
public:
	explicit IndentableStream(ostream& os)
		: ostream(&m_indentationBuffer)
		, m_indentationBuffer(os.rdbuf())
		, m_itemsPerLine(1)
	{
	}

	IndentableStream& indent()
	{
		m_indentationBuffer.indent();
		return *this;
	}

	IndentableStream& undent()
	{
		m_indentationBuffer.undent();
		return *this;
	}

	friend std::ostream& itemsPerLine(std::ostream& out, size_t ipl)
	{
		const auto is = dynamic_cast<IndentableStream*>(&out);
		if (is)
		{
			is->m_itemsPerLine = ipl;
		}

		return out;
	}

	size_t itemsPerLine() const { return m_itemsPerLine; }

	size_t itemsPrecision() const { return m_itemsPrecision; }

private:
	IndentationBuffer m_indentationBuffer;
	size_t m_itemsPerLine;
	size_t m_itemsPrecision;
};

inline std::ostream& indent(std::ostream& stream)
{
	auto is = dynamic_cast<IndentableStream*>(&stream);
	return is ? is->indent() : stream;
}

inline std::ostream& undent(std::ostream& stream)
{
	auto is = dynamic_cast<IndentableStream*>(&stream);
	return is ? is->undent() : stream;
}

template<typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& iterable)
{
	out << std::fixed;

	const auto itemsIndent = '\t';
	const auto newLineIndent = std::string(",\n") + itemsIndent;
	const auto itemSeparator = std::string(",\t");
	const auto noSeparator = std::string("");

	out << '[' << endl << itemsIndent;

	const auto* separator = &noSeparator;

	auto is = dynamic_cast<IndentableStream*>(&out);
	const int itemsPerLine = static_cast<int>(is ? is->itemsPerLine() : 10);
	const int precision = static_cast<int>(is ? is->itemsPrecision() : 3);

	int counter = itemsPerLine;

	for (auto it = iterable.begin(); it != iterable.end(); ++it)
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

	return out;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& out, const std::pair<K, V>& pair)
{
	out << '{' << '"' << pair.first << '"' << ':' << pair.second << '}';
	return out;
}


