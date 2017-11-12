#pragma once
#include "ExportableItem.h"
#include "ExportablePrimitive.h"

class ExportableMesh : public ExportableItem
{
public:
	ExportableMesh(const MDagPath& dagPath, GLTF::Node& node);
	virtual ~ExportableMesh();

	GLTF::Mesh mesh;

private:
	std::vector<std::unique_ptr<ExportablePrimitive>> m_primitives;
};

