#pragma once
#include "MeshSemantics.h"
#include "MeshVertices.h"
#include "MeshIndices.h"
#include "MeshRenderable.h"

typedef std::vector<std::unique_ptr<MeshRenderable>> MeshRenderables;

class Mesh
{
public:
	Mesh(const MDagPath& dagPath);
	virtual ~Mesh();

	void dump(const std::string& name, const std::string& indent) const;

	const MeshSemantics& semantics() const { return *m_semantics; }
	const MeshVertices& vertices() const { return *m_vertices; }
	const MeshIndices& indices() const { return *m_indices; }
	const MeshRenderables& renderables() const { return m_renderables; }

private:
	MDagPath m_dagPath;

	std::unique_ptr<MeshSemantics> m_semantics;
	std::unique_ptr<MeshVertices> m_vertices;
	std::unique_ptr<MeshIndices> m_indices;
	MeshRenderables m_renderables;
};

