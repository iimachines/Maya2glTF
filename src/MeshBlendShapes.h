#pragma once
#include "MeshShape.h"

struct MeshBlendShape
{
	MeshBlendShape(const MFnMesh& fnMesh, const MPlug weightPlug) : shape(fnMesh), weightPlug(weightPlug)
	{
	}

	const MeshShape shape;
	const MPlug weightPlug;
};

typedef std::vector<std::unique_ptr<MeshBlendShape>> MeshBlendShapeVector;

class MeshBlendShapes
{
public:
	MeshBlendShapes(MObject blendShapeController);
	virtual ~MeshBlendShapes();

	void dump(const std::string& name, const std::string& indent) const;

	const MeshBlendShapeVector& blendShapes() const { return m_blendShapes; }


private:
	MObject getOrCreateOutgoingShapeNode(MPlug& sourcePlug) const;
	MObject getOrCreateIncomingShapeNode(const MPlug& plug) const;
	std::unique_ptr<MeshShape> m_baseShape;
	MeshBlendShapeVector m_blendShapes;
};

