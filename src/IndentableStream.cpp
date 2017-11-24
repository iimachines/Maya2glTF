#include "externals.h"
#include "IndentableStream.h"

ostream& prefix(ostream& stream)
{
	tm buf;
	const auto now = std::chrono::system_clock::now();
	const auto time = std::chrono::system_clock::to_time_t(now);
	localtime_s(&buf, &time);
	stream << "maya2glTF [" << std::put_time(&buf, "%T") << "] ";
	return stream;
}

IndentationScope&& IndentableStream::scope()
{
	return std::move(IndentationScope(*this));
}

IndentationBuffer::IndentationBuffer(std::streambuf* sbuf)
	: m_sbuf(sbuf)
	, m_indentationLevel(1)
	, m_shouldIndent(true)
{
}

std::basic_streambuf<char>::int_type IndentationBuffer::overflow(const int_type c)
{
	if (traits_type::eq_int_type(c, traits_type::eof()))
		return m_sbuf->sputc(c);

	if (m_shouldIndent)
	{
		fill_n(std::ostreambuf_iterator<char>(m_sbuf), m_indentationLevel, '\t');
		m_shouldIndent = false;
	}

	if (traits_type::eq_int_type(m_sbuf->sputc(c), traits_type::eof()))
		return traits_type::eof();

	if (traits_type::eq_int_type(c, traits_type::to_char_type('\n')))
		m_shouldIndent = true;

	return traits_type::not_eof(c);
}

