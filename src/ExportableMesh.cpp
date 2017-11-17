#include "externals.h"
#include "Mesh.h"
#include "ExportableMesh.h"
#include "ExportablePrimitive.h"
#include "Arguments.h"

ExportableMesh::ExportableMesh(const MDagPath& shapeDagPath, ExportableResources& resources, const Arguments& args)
{
	Mesh mayaMesh(shapeDagPath);

	if (args.dumpMaya)
	{
		mayaMesh.dump(shapeDagPath.fullPathName().asChar(), "");
	}

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
