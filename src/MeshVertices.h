#pragma once

#include "SceneTypes.h"
#include "Spans.h"
#include "MeshSetNames.h"

/** The vertices of a single Maya mesh */
class MeshVertices
{
public:
	MeshVertices(const MeshSetNames& names, const MFnMesh& mesh, MSpace::Space space = MSpace::kObject);
	virtual ~MeshVertices();

	gsl::span<const float> floatSpan(const Semantic::Kind semantic, SetIndex setIndex) const
	{
		switch (semantic)
		{
		case Semantic::POSITION:
			assert(setIndex == 0);
			return reinterpret_span<float>(span(m_positions));
		case Semantic::NORMAL:
			assert(setIndex == 0);
			return reinterpret_span<float>(span(m_normals));
		case Semantic::COLOR:
			return reinterpret_span<float>(span(m_colorSets.at(setIndex)));
		case Semantic::TEXCOORD:
			return reinterpret_span<float>(span(m_uvSets.at(setIndex)));
		default:
			assert(false);
			return gsl::span<float>();
		}
	}

	const MFloatPointArray&		positions() const { return m_positions; }
	const MFloatVectorArray&	normals() const { return m_normals; }

	const std::map<SetIndex, Float2Vector>&	uvSets() const { return m_uvSets; }
	const std::map<SetIndex, MColorArray>&	colorSets() const { return m_colorSets; }

	void dump(const std::string& name, const std::string& indent) const;

private:
	MFloatPointArray m_positions;
	MFloatVectorArray m_normals;
	std::map<SetIndex, Float2Vector> m_uvSets;
	std::map<SetIndex, MColorArray> m_colorSets;

	DISALLOW_COPY_AND_ASSIGN(MeshVertices);
};
