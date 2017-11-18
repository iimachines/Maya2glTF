#pragma once
#include "MeshShape.h"

struct MeshBlendShapeEntry
{
	MeshBlendShapeEntry(const MFnMesh& fnMesh, const MPlug weightPlug) : shape(fnMesh, true), weightPlug(weightPlug)
	{
	}

	const MeshShape shape;
	const MPlug weightPlug;
};

typedef std::vector<std::unique_ptr<MeshBlendShapeEntry>> MeshBlendShapeEntries;

class MeshBlendShapes
{
public:
	MeshBlendShapes(MObject blendShapeController);
	virtual ~MeshBlendShapes();

	void dump(const std::string& name, const std::string& indent) const;

	bool empty() const { return m_baseShape == nullptr || m_entries.size() == 0;  }

	const MeshBlendShapeEntries& entries() const { return m_entries; }
	const MeshShape* baseShape() const { return m_baseShape.get(); }

private:
	MObject getOrCreateOutgoingShapeNode(MPlug& sourcePlug) const;
	MObject getOrCreateIncomingShapeNode(const MPlug& plug) const;
	std::unique_ptr<MeshShape> m_baseShape;
	MeshBlendShapeEntries m_entries;
};

