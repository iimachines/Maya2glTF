#pragma once

#include "SceneTypes.h"

struct MeshSemantic
{
	MeshSemantic(const Semantic::Kind kind, const SetIndex setIndex, const MString& setName, const int elementCount)
		: kind(kind)
		, setName(setName)
		, setIndex(setIndex)
		, elementCount(elementCount)
	{
	}

	MeshSemantic(const MeshSemantic& from)
		: kind(from.kind)
		, setName(from.setName)
		, setIndex(from.setIndex)
		, elementCount(from.elementCount)
	{
	}

	void dump(const std::string& indent) const;

	const Semantic::Kind kind;
	const MString setName;
	const SetIndex setIndex;
	const int elementCount;
};

typedef std::vector<MeshSemantic> MeshSemanticVector;
typedef std::array<MeshSemanticVector, Semantic::COUNT> MeshSemanticsArray;

class MeshSemantics
{
public:
	MeshSemantics(const MFnMesh& mesh);
	virtual ~MeshSemantics();

	const MeshSemanticsArray& items() const { return m_items; }

	const MeshSemanticVector& at(const Semantic::Kind kind) const { return m_items.at(kind); }

	void dump(const std::string& name, const std::string& indent) const;

private:
	std::array<std::vector<MeshSemantic>, Semantic::COUNT> m_items;
};

