#include "externals.h"
#include "Mesh.h"
#include "ExportableMesh.h"
#include "ExportablePrimitive.h"

ExportableMesh::ExportableMesh(const MDagPath& shapeDagPath, ExportableResources& resources)
{
	Mesh mayaMesh(shapeDagPath);

	for (auto&& renderable : mayaMesh.renderables())
	{
		auto exportablePrimitive = new ExportablePrimitive(*renderable, resources);
		m_primitives.emplace_back(exportablePrimitive);

		glMesh.primitives.push_back(&exportablePrimitive->glPrimitive);
	}
}

ExportableMesh::~ExportableMesh()
{
}
