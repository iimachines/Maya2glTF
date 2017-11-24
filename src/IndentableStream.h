#pragma once

#include "externals.h"

/** Prints the common prefix ("maya2glTF@<time>: ") */
ostream& prefix(ostream& stream);

class IndentationBuffer : public std::streambuf
{
public:
	IndentationBuffer(std::streambuf* sbuf);

	int indentationLevel() const { return m_indentationLevel; }

	void indent() { ++m_indentationLevel; }

	void deindent() { m_indentationLevel = std::max(0, m_indentationLevel - 1); }

protected:

	int_type overflow(const int_type c) override;

	std::streambuf* m_sbuf;
	int m_indentationLevel;
	bool m_shouldIndent;
};

class IndentableStream : public ostream
{
public:
	explicit IndentableStream(ostream& os)
		: ostream(&m_ib)
		  , m_ib(os.rdbuf())
	{
	}

	IndentableStream& indent()
	{
		m_ib.indent();
		return *this;
	}

	IndentableStream& deindent()
	{
		m_ib.deindent();
		return *this;
	}

	class IndentationScope&& scope();

	static friend std::ostream& indent(std::ostream& stream)
	{
		auto is = dynamic_cast<IndentableStream*>(&stream);
		return is ? is->indent() : stream;
	}

	static friend std::ostream& deindent(std::ostream& stream)
	{
		auto is = dynamic_cast<IndentableStream*>(&stream);
		return is ? is->indent() : stream;
	}

private:
	IndentationBuffer m_ib;
};

class IndentationScope
{
public:
	explicit IndentationScope(IndentableStream& out):out(&out)
	{
		out.indent();
	}


	IndentationScope(IndentationScope&& other) noexcept 
		: out(other.out)
	{
		other.out = nullptr;
	}

	IndentationScope(const IndentationScope& other)
		: out(other.out)
	{
	}

	IndentationScope& operator=(const IndentationScope& other)
	{
		if (this != &other)
		{
			out = other.out;
		}
		return *this;
	}

	IndentationScope& operator=(IndentationScope&& other) noexcept
	{
		if (this != &other)
		{
			out = other.out;
			other.out = nullptr;
		}
		return *this;
	} 

	~IndentationScope()
	{
		if (out)
		{
			out->deindent();
			out = nullptr;
		}
	}

private:
	IndentableStream* out;
};
