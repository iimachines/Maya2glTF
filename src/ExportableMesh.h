#pragma once
#include "ExportableItem.h"
#include "ExportablePrimitive.h"

class Arguments;
class Mesh;

class ExportableMesh : public ExportableItem
{
public:
	ExportableMesh(const Mesh& mayaMesh);
	virtual ~ExportableMesh();

	GLTF::Mesh glMesh;

private:
	std::vector<std::unique_ptr<ExportablePrimitive>> m_primitives;
};

