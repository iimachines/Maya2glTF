#pragma once
#include "MeshShape.h"

struct MeshBlendShapeEntry
{
	MeshBlendShapeEntry(const MFnMesh& fnMesh, const Arguments& args, const MPlug& weightPlug)
	: shape(fnMesh, args, true)
	, weightPlug(weightPlug)
	{
	}

	const MeshShape shape;
	const MPlug weightPlug;
};

typedef std::vector<std::unique_ptr<MeshBlendShapeEntry>> MeshBlendShapeEntries;

class MeshBlendShapes
{
public:
	MeshBlendShapes(MObject blendShapeNode, const Arguments& args);
	virtual ~MeshBlendShapes();

	void dump(class IndentableStream& cout, const std::string& name) const;

	bool empty() const { return m_baseShape == nullptr || m_entries.size() == 0;  }

	const MeshBlendShapeEntries& entries() const { return m_entries; }
	const MeshShape* baseShape() const { return m_baseShape.get(); }

private:
	MObject getOrCreateOutputShape(MPlug& sourcePlug, MObject& createdMesh) const;

	std::unique_ptr<MeshShape> m_baseShape;
	MeshBlendShapeEntries m_entries;
	MObject m_tempOutputMesh;
};

