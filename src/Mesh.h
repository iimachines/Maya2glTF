#pragma once

#include "MeshShape.h"
#include "MeshRenderables.h"

class Arguments;

class Mesh
{
public:
	Mesh(const MDagPath& dagPath, const Arguments& args);
	~Mesh();

	void dump(IndentableStream& out, const std::string& name) const;

	bool isEmpty() const { return m_shapes.empty(); }

	const MeshShape& shape() const { return *m_shapes.at(0); }

	const MeshShapes& shapes() const { return m_shapes; }

	const MeshRenderables& renderables() const { return *m_renderables; }

private:
	DISALLOW_COPY_MOVE_ASSIGN(Mesh);

	MeshShapes m_shapes;
	std::unique_ptr<MeshRenderables> m_renderables;

	MObject m_tempOutputMesh;

	MObject getOrCreateOutputShape(MPlug& outputGeometryPlug, MObject& createdMesh) const;

	static MObject tryExtractBlendController(const MFnMesh& fnMesh);
};

