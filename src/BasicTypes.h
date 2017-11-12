#pragma once

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  void operator=(const TypeName&) = delete

typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

typedef std::string Name;
typedef std::vector<Name> NameVector;

typedef std::array<float, 1> Float1;
typedef std::array<float, 2> Float2;
typedef std::array<float, 3> Float3;
typedef std::array<float, 4> Float4;

typedef std::array<int, 2> Int2;
typedef std::array<int, 3> Int3;
typedef std::array<int, 4> Int4;

typedef std::array<uint, 2> UInt2;
typedef std::array<uint, 3> UInt3;
typedef std::array<uint, 4> UInt4;

typedef std::array<Float3, 3> Matrix3x3;
typedef std::array<Float3, 4> Matrix3x4;
typedef std::array<Float4, 4> Matrix4x4;

typedef std::vector<float> FloatVector;
typedef std::vector<Float2> Float2Vector;
typedef std::vector<Float3> Float3Vector;
typedef std::vector<Float4> Float4Vector;
typedef std::vector<unsigned int> UIntVector;
typedef std::vector<Matrix4x4> Matrix4x4Vector;

typedef std::vector<std::string> StringVector;

template<typename>
struct array_size;

template<typename T, size_t N>
struct array_size<std::array<T, N> > {
	static size_t const size = N;
};
