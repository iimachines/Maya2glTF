#pragma once
#include "SceneTypes.h"
#include "Spans.h"

class MeshVertices
{
public:
	MeshVertices(MFnMesh& mesh, MSpace::Space space = MSpace::kObject);
	virtual ~MeshVertices();

	const gsl::span<const float> floatSpan(const Semantic semantic) const
	{
		switch (semantic)
		{
		case POSITION:
			return reinterpret_span<float>(span(m_Positions));
		case NORMAL:
			return reinterpret_span<float>(span(m_Normals));
		case TANGENT:
			return reinterpret_span<float>(span(m_Tangents));
		case COLOR:
			return reinterpret_span<float>(span(m_Colors));
		case TEXCOORD:
			return reinterpret_span<float>(span(m_TexCoords));
		default:
			assert(false);
			return gsl::span<float>();
		}
	}

	const MFloatPointArray&		positions() const { return m_Positions; }
	const MFloatVectorArray&	normals() const { return m_Normals; }
	const Float2Vector&			texCoords() const { return m_TexCoords; }
	const MFloatVectorArray&	tangents() const { return m_Tangents; }
	const MColorArray&			colors() const { return m_Colors; }

private:
	MFloatPointArray			m_Positions;
	MFloatVectorArray			m_Normals;
	Float2Vector				m_TexCoords;
	MFloatVectorArray			m_Tangents;
	MColorArray					m_Colors;

	DISALLOW_COPY_AND_ASSIGN(MeshVertices);
};
