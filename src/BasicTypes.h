#pragma once

typedef uint8_t byte;
typedef uint16_t ushort;

typedef std::array<float, 1> Float1;
typedef std::array<float, 2> Float2;
typedef std::array<float, 3> Float3;
typedef std::array<float, 4> Float4;

typedef std::array<Float4, 4> Float4x4;

typedef std::vector<float> FloatVector;
typedef std::vector<Float2> Float2Vector;

template<typename>
struct array_size;

template<typename T, size_t N>
struct array_size<std::array<T, N> > {
	static size_t const size = N;
};


template<typename T, size_t N>
const std::array<T,N>&& reinterpret_array(const T(&items)[N])
{
	return std::move(*reinterpret_cast<const std::array<T, N>*>(items));
}

