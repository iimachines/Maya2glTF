#pragma once

#include "MeshSemantics.h"
#include "MeshVertices.h"
#include "MeshIndices.h"

class MeshShape
{
public:
	MeshShape(const MFnMesh& fnMesh, const Arguments& args, int shapeIndex);
	virtual ~MeshShape() = default;

	void dump(class IndentableStream& out, const std::string& name) const;

	const int shapeIndex;
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

