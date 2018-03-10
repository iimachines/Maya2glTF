#pragma once
#include "MeshShape.h"

class MeshBlendShapeEntry
{
public:
	MeshBlendShapeEntry(const MFnMesh& fnMesh, const int shapeIndex, const Arguments& args, const MPlug& weightPlug)
	: shape(fnMesh, args, shapeIndex)
	, weightPlug(weightPlug)
	{
	}

	~MeshBlendShapeEntry() = default;

	const MeshShape shape;
	const MPlug weightPlug;

private:
	DISALLOW_COPY_MOVE_ASSIGN(MeshBlendShapeEntry);
};

typedef std::vector<std::unique_ptr<MeshBlendShapeEntry>> MeshBlendShapeEntries;

class MeshBlendShapes
{
public:
	MeshBlendShapes(MObject blendShapeNode, const Arguments& args);
	virtual ~MeshBlendShapes();

	void dump(class IndentableStream& out, const std::string& name) const;

	bool empty() const { return m_baseShape == nullptr || m_entries.empty();  }

	const MeshBlendShapeEntries& entries() const { return m_entries; }
	const MeshShape* baseShape() const { return m_baseShape.get(); }

private:

	DISALLOW_COPY_MOVE_ASSIGN(MeshBlendShapes);

	MObject getOrCreateOutputShape(MPlug& outputGeometryPlug, MObject& createdMesh) const;

	std::unique_ptr<MeshShape> m_baseShape;
	MeshBlendShapeEntries m_entries;
	MObject m_tempOutputMesh;
};

