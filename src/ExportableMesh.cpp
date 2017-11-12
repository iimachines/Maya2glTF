#include "externals.h"
#include "Mesh.h"
#include "ExportableMesh.h"

ExportableMesh::ExportableMesh(const MDagPath& dagPath, GLTF::Node& node)
{
	const Mesh mayaMesh(dagPath);
	for (auto&& pair : mayaMesh.renderables())
	{
		auto exportablePrimitive = new ExportablePrimitive(*pair.second);
		m_primitives.emplace_back(exportablePrimitive);
		mesh.primitives.push_back(&exportablePrimitive->primitive);
	}
}

ExportableMesh::~ExportableMesh()
{
}
