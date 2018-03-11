#pragma once

#include "MeshSemantics.h"
#include "MeshVertices.h"
#include "MeshIndices.h"

class MeshShape
{
public:
	MeshShape(const MFnMesh& fnMesh, const Arguments& args, ShapeIndex shapeIndex, const MPlug& weightPlug);
	virtual ~MeshShape() = default;

	void dump(class IndentableStream& out, const std::string& name) const;

	const ShapeIndex shapeIndex; 
	const MPlug weightPlug; // isNull of main shape
	const float initialWeight = 0; 

	const MDagPath& dagPath() const { return m_dagPath; }
	const MeshSemantics& semantics() const { return *m_semantics; }
	const MeshVertices& vertices() const { return *m_vertices; }
	const MeshIndices& indices() const { return *m_indices; }

private:
	MDagPath m_dagPath;

	std::unique_ptr<MeshSemantics> m_semantics;
	std::unique_ptr<MeshVertices> m_vertices;
	std::unique_ptr<MeshIndices> m_indices;

	DISALLOW_COPY_MOVE_ASSIGN(MeshShape);
};

// main-shape followed by blend-shapes.
// TODO: Use a map?
typedef std::vector<std::unique_ptr<MeshShape>> MeshShapes;


