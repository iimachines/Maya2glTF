#pragma once
#include "BasicTypes.h"

// <0 means an invalid index
typedef int Index;

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

enum Semantic
{
	POSITION,
	NORMAL,
	TANGENT,
	COLOR,
	TEXCOORD,
	NUM_SEMANTICS,
};

// Get the number of components per semantic 
// (e.g. the "dimension" of the semantic. bad terminology?)
inline size_t dimensionOf(Semantic s)
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
