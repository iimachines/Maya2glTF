#pragma once

#include "SceneTypes.h"

struct VertexElementSetDescription
{
	VertexElementSetDescription(const Semantic::Kind semantic, const SetIndex setIndex, const MString& setName, const int elementCount)
		: semantic(semantic)
		, setName(setName)
		, setIndex(setIndex)
		, elementCount(elementCount)
	{
	}

	VertexElementSetDescription(const VertexElementSetDescription& from)
		: semantic(from.semantic)
		, setName(from.setName)
		, setIndex(from.setIndex)
		, elementCount(from.elementCount)
	{
	}

	void dump(class IndentableStream& cout, const std::string& name) const;

	const Semantic::Kind semantic;
	const MString setName;
	const SetIndex setIndex;
	const int elementCount;
};

typedef std::vector<VertexElementSetDescription> VertexComponentSetDescriptionPerSetIndex;
typedef std::array<VertexComponentSetDescriptionPerSetIndex, Semantic::COUNT> VertexComponentSetDescriptionPerSetIndexTable;

class MeshSemantics
{
public:
	MeshSemantics(const MFnMesh& mesh, bool isBlendShape);
	virtual ~MeshSemantics();

	const VertexComponentSetDescriptionPerSetIndexTable& table() const { return m_table; }

	const VertexComponentSetDescriptionPerSetIndex& descriptions(const Semantic::Kind kind) const { return m_table.at(kind); }

	void dump(class IndentableStream& cout, const std::string& name) const;

private:
	VertexComponentSetDescriptionPerSetIndexTable m_table;
};

