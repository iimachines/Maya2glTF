#pragma once
#include "basicTypes.h"

// <0 means an invalid index
typedef __int32 Index;

/** Maya uses strings to identify color and texture-coordinate sets. We use indices */
typedef int SetIndex;

typedef Float3 Position;
typedef Float4 Rotation; // a quaternion
typedef Float3 Scale; 
typedef Float3 Normal;
typedef Float2 TexCoord;
typedef Float4 Color;

typedef Float4 MainShapeTangent;	// 3D tangent  + bitangent sign (chirality)
typedef Float3 BlendShapeTangent;	// 3D tangent only

typedef std::vector<Position> PositionVector;
typedef std::vector<Rotation> RotationVector;
typedef std::vector<Scale> ScaleVector;
typedef std::vector<Normal> NormalVector;
typedef std::vector<TexCoord> TexCoordVector;
typedef std::vector<Color> ColorVector;
typedef std::vector<Index> IndexVector;

typedef gsl::span<Index> IndexSpan;

/** Index of a Maya shape instance */
typedef int InstanceIndex;

/** Index of a Maya material */
typedef int ShaderIndex;

typedef size_t Hash;

enum PrimitiveKind
{
	// TODO: Support other primitives
	TRIANGLE_LIST
};

namespace Semantic
{
	enum Kind
	{
		INVALID = -1,
		POSITION,
		NORMAL,
		COLOR,
		TEXCOORD,
		TANGENT,
		COUNT
	};

	inline Kind from(int s)
	{
		assert(s >= 0 && s < COUNT);
		return static_cast<Kind>(s);
	}

	// Get the number of float components per semantic 
	inline int dimension(const Kind s, const int shapeIndex)
	{
		switch (s)
		{
		case POSITION:	return array_size<Position>::size;
		case NORMAL:	return array_size<Normal>::size;
		case COLOR:		return array_size<Color>::size;
		case TEXCOORD:	return array_size<TexCoord>::size;
		case TANGENT:	return shapeIndex > 0 ? array_size<BlendShapeTangent>::size : array_size<MainShapeTangent>::size;
		default: assert(false); return 0;
		}
	}
		
	inline const char* name(const Kind s)
	{
		switch (s)
		{
		case POSITION:	return "POSITION";
		case NORMAL:	return "NORMAL";
		case COLOR:		return "COLOR";
		case TEXCOORD:	return "TEXCOORD";
		case TANGENT:	return "TANGENT";
		default: assert(false); return "UNKNOWN";
		}
	}

	template<typename T>
	size_t totalSetCount(const T& table) 
	{
		size_t count = 0;

		for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
		{
			count += table.at(semanticIndex).size();
		}

		return count;
	}
}
