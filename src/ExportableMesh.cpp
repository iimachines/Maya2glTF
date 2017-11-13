#include "externals.h"
#include "Mesh.h"
#include "ExportableMesh.h"

ExportableMesh::ExportableMesh(const MDagPath& dagPath)
{
	const Mesh mayaMesh(dagPath);
	mayaMesh.dump("maya-mesh", "");

	for (auto&& pair : mayaMesh.renderables())
	{
		auto exportablePrimitive = new ExportablePrimitive(*pair.second);
		m_primitives.emplace_back(exportablePrimitive);
		glMesh.primitives.push_back(&exportablePrimitive->glPrimitive);
	}
}

ExportableMesh::~ExportableMesh()
{
}
