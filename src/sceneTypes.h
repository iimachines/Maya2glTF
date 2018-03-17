#pragma once

#include "basicTypes.h"
#include "ShapeIndex.h"

// <0 means an invalid index
typedef int Index;

/** Maya uses strings to identify color and texture-coordinate sets. We use indices */
typedef int SetIndex;

/** We use 32-bit indices, until saving */
typedef int VertexIndex;

typedef Float3 Position;
typedef Float4 Rotation; // a quaternion
typedef Float3 Scale; 
typedef Float3 Normal;
typedef Float2 TexCoord;
typedef Float4 Color;
typedef Float4 JointWeights;
typedef Float4 JointIndices; // TODO: these should become integers, but that requires a lot of refactoring.

typedef Float4 MainShapeTangent;	// 3D tangent  + bitangent sign (chirality)
typedef Float3 BlendShapeTangent;	// 3D tangent only

typedef std::vector<Position> PositionVector;
typedef std::vector<Rotation> RotationVector;
typedef std::vector<Scale> ScaleVector;
typedef std::vector<Normal> NormalVector;
typedef std::vector<TexCoord> TexCoordVector;
typedef std::vector<Color> ColorVector;
typedef std::vector<Index> IndexVector;
typedef std::vector<JointWeights> JointWeightsVector;
typedef std::vector<JointIndices> JointIndicesVector;

typedef gsl::span<Index> IndexSpan;

/** Maya shape instance number */
typedef size_t InstanceNumber;

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
		WEIGHTS,
		JOINTS,
		COUNT
	};

	typedef std::array<Kind, COUNT> SemanticKinds;
	const SemanticKinds& kinds();

	inline Kind from(int s)
	{
		assert(s >= 0 && s < COUNT);
		return static_cast<Kind>(s);
	}

	// Get the number of float components per semantic 
	inline int dimension(const Kind s, const ShapeIndex& shapeIndex)
	{
		switch (s)
		{
		case POSITION:	return array_size<Position>::size;
		case NORMAL:	return array_size<Normal>::size;
		case COLOR:		return array_size<Color>::size;
		case TEXCOORD:	return array_size<TexCoord>::size;
		case TANGENT:	return shapeIndex.isBlendShapeIndex() ? array_size<BlendShapeTangent>::size : array_size<MainShapeTangent>::size;
		case WEIGHTS:	return array_size<JointWeights>::size;
		case JOINTS:	return array_size<JointIndices>::size;
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
		case WEIGHTS:	return "WEIGHTS";
		case JOINTS:	return "JOINTS";
		default: assert(false); return "UNKNOWN";
		}
	}

	inline Kind parse(const std::string& s)
	{
		for (auto kind: kinds())
		{
			if (s == name(kind))
				return kind;
		}
		return INVALID;
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

