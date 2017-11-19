#pragma once

#include "sceneTypes.h"

struct VertexComponentSetDescription
{
	VertexComponentSetDescription(const Semantic::Kind semantic, const SetIndex setIndex, const MString& setName, const int elementCount)
		: semantic(semantic)
		, setName(setName)
		, setIndex(setIndex)
		, elementCount(elementCount)
	{
	}

	VertexComponentSetDescription(const VertexComponentSetDescription& from)
		: semantic(from.semantic)
		, setName(from.setName)
		, setIndex(from.setIndex)
		, elementCount(from.elementCount)
	{
	}

	void dump(const std::string& name, const std::string& indent) const;

	const Semantic::Kind semantic;
	const MString setName;
	const SetIndex setIndex;
	const int elementCount;
};

typedef std::vector<VertexComponentSetDescription> VertexComponentSetDescriptionPerSetIndex;
typedef std::array<VertexComponentSetDescriptionPerSetIndex, Semantic::COUNT> VertexComponentSetDescriptionPerSetIndexTable;

class MeshSemantics
{
public:
	MeshSemantics(const MFnMesh& mesh, bool isBlendShape);
	virtual ~MeshSemantics();

	const VertexComponentSetDescriptionPerSetIndexTable& table() const { return m_table; }

	const VertexComponentSetDescriptionPerSetIndex& descriptions(const Semantic::Kind kind) const { return m_table.at(kind); }

	void dump(const std::string& name, const std::string& indent) const;

private:
	VertexComponentSetDescriptionPerSetIndexTable m_table;
};

