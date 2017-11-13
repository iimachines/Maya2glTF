#pragma once
#include "ExportableItem.h"
#include "ExportablePrimitive.h"

class ExportableMesh : public ExportableItem
{
public:
	ExportableMesh(const MDagPath& dagPath);
	virtual ~ExportableMesh();

	GLTF::Mesh glMesh;

private:
	std::vector<std::unique_ptr<ExportablePrimitive>> m_primitives;
};

