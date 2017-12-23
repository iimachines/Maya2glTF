#pragma once
#include "ExportableItem.h"

class ExportableResources;
class ExportablePrimitive;
class Arguments;
class Mesh;

class ExportableMesh : public ExportableItem
{
public:
	ExportableMesh(const MDagPath& shapeDagPath, ExportableResources& resources);
	virtual ~ExportableMesh();

	GLTF::Mesh glMesh;

private:
	std::vector<std::unique_ptr<ExportablePrimitive>> m_primitives;
};

