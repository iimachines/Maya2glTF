#pragma once

#include "MeshSemantics.h"
#include "MeshVertices.h"
#include "MeshIndices.h"

class MeshShape
{
public:
	MeshShape(const MFnMesh& mesh);
	MeshShape(const MDagPath& dagPath);
	virtual ~MeshShape();

	void dump(const std::string& name, const std::string& indent) const;

	const MeshSemantics& semantics() const { return *m_semantics; }
	const MeshVertices& vertices() const { return *m_vertices; }
	const MeshIndices& indices() const { return *m_indices; }

private:
	MDagPath m_dagPath;

	std::unique_ptr<MeshSemantics> m_semantics;
	std::unique_ptr<MeshVertices> m_vertices;
	std::unique_ptr<MeshIndices> m_indices;
};

