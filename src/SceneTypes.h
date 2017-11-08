#pragma once
#include "BasicTypes.h"

// <0 means an invalid index
typedef __int32 Index;

typedef Float4 Position;
typedef Float3 Normal;
typedef Float3 Tangent;
typedef Float2 TexCoord;
typedef Float4 Color;

typedef std::vector<Position> PositionVector;
typedef std::vector<Normal> NormalVector;
typedef std::vector<Tangent> TangentVector;
typedef std::vector<TexCoord> TexCoordVector;
typedef std::vector<Color> ColorVector;
typedef std::vector<Index> IndexVector;

enum PrimitiveKind
{
	// TODO: Support other primitives
	TRIANGLE_LIST
};

enum Limitations
{
	MAX_TEXTURES_PER_VERTEX = 4,
	MAX_SKIN_INFLUENCES_PER_VERTEX = 4,
};

namespace Semantic
{
	enum Kind
	{
		POSITION,
		NORMAL,
		TANGENT,
		COLOR,
		TEXCOORD,
		COUNT,
	};

	inline Kind from(int s)
	{
		assert(s >= 0 && s < COUNT);
		return static_cast<Kind>(s);
	}

	// Get the number of components per semantic 
	inline size_t components(const Kind s)
	{
		switch (s)
		{
		case POSITION:	return array_size<Position>::size;
		case NORMAL:	return array_size<Normal>::size;
		case TANGENT:	return array_size<Tangent>::size;
		case COLOR:		return array_size<Color>::size;
		case TEXCOORD:	return array_size<TexCoord>::size;
		default: assert(false); return 0;
		}
	}

	inline const char* name(const Kind s)
	{
		switch (s)
		{
		case POSITION:	return "POSITION";
		case NORMAL:	return "NORMAL";
		case TANGENT:	return "TANGENT";
		case COLOR:		return "COLOR";
		case TEXCOORD:	return "TEXCOORD";
		default: assert(false); return "";
		}
	}
}
