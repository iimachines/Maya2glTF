#include "externals.h"
#include "Mesh.h"
#include "ExportableMesh.h"

ExportableMesh::ExportableMesh(const Mesh& mayaMesh)
{
	for (auto&& renderable : mayaMesh.renderables())
	{
		auto exportablePrimitive = new ExportablePrimitive(*renderable);
		m_primitives.emplace_back(exportablePrimitive);
		glMesh.primitives.push_back(&exportablePrimitive->glPrimitive);
	}
}

ExportableMesh::~ExportableMesh()
{
}
