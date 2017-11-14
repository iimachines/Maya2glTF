#pragma once

#include "sceneTypes.h"

struct SetDescription
{
	SetDescription(const SetIndex setIndex, const MString& setName, const int elementCount)
		: setName(setName)
		, setIndex(setIndex)
		, elementCount(elementCount)
	{
	}

	SetDescription(const SetDescription& from)
		: setName(from.setName)
		, setIndex(from.setIndex)
		, elementCount(from.elementCount)
	{
	}

	void dump(const std::string& name, const std::string& indent) const;

	const MString setName;
	const SetIndex setIndex;
	const int elementCount;
};

typedef std::vector<SetDescription> SetDescriptionPerSetIndex;
typedef std::array<SetDescriptionPerSetIndex, Semantic::COUNT> SetDescriptionPerSetIndexTable;


class MeshSemantics
{
public:
	MeshSemantics(const MFnMesh& mesh);
	virtual ~MeshSemantics();

	const SetDescriptionPerSetIndexTable& table() const { return m_table; }

	const SetDescriptionPerSetIndex& descriptions(const Semantic::Kind kind) const { return m_table.at(kind); }

	size_t totalSetCount() const;

	void dump(const std::string& name, const std::string& indent) const;

private:
	SetDescriptionPerSetIndexTable m_table;
};

