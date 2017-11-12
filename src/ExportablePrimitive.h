#pragma once

#include "sceneTypes.h"
#include "MeshRenderable.h"

typedef std::vector<std::unique_ptr<GLTF::Accessor>> MeshAccessorPerSetIndex;
typedef std::array<MeshAccessorPerSetIndex, Semantic::COUNT> MeshAccessorPerSetIndexTable;

class ExportablePrimitive
{
public:
	ExportablePrimitive(const MeshRenderable& renderable);
	virtual ~ExportablePrimitive();

	GLTF::Primitive primitive;
	GLTF::Buffer buffer;
	GLTF::BufferView view;
	std::unique_ptr<GLTF::Accessor> indices;
	MeshAccessorPerSetIndexTable accessorTable;

private:
	std::vector<uint8> m_data;

	GLTF::Accessor* createAccessor(const Semantic::Kind semantic, const int offset, const int count);
};
