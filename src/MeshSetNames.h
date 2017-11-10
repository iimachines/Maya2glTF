#pragma once

#include "SceneTypes.h"

class MeshSetNames
{
public:
	MeshSetNames(const MFnMesh& mesh);
	virtual ~MeshSetNames();

	int numSetsOf(const Semantic::Kind semantic) const
	{
		switch (semantic)
		{
		case Semantic::POSITION:
			return 1;
		case Semantic::NORMAL:
			return 1;
		case Semantic::COLOR:
			return m_colors.length();
		case Semantic::TEXCOORD:
			return m_texCoords.length();
		default:
			assert(false);
			return 0;
		}
	}

	const MStringArray& colors() const { return m_colors; }
	const MStringArray& texCoords() const { return m_texCoords; }

	void dump(const std::string& name, const std::string& indent) const;

private:
	MStringArray m_colors;
	MStringArray m_texCoords;
};

