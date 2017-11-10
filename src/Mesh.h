#pragma once
#include "MeshSetNames.h"
#include "MeshVertices.h"
#include "MeshIndices.h"

class Mesh
{
public:
	Mesh(MDagPath dagPath);
	virtual ~Mesh();

	void dump(const std::string& name, const std::string& indent) const;

private:
	MDagPath m_dagPath;

	std::unique_ptr<MeshSetNames> m_setNames;
	std::unique_ptr<MeshVertices> m_vertices;
	std::unique_ptr<MeshIndices> m_indices;
};

