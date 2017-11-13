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

	GLTF::Primitive glPrimitive;
	GLTF::Buffer glBuffer;
	GLTF::BufferView glView;
	std::unique_ptr<GLTF::Accessor> glIndices;
	MeshAccessorPerSetIndexTable glAccessorTable;

private:
	std::vector<uint8> m_data;

	std::unique_ptr<GLTF::Accessor> createAccessor(const Semantic::Kind semantic, const int offset, const int count);
};
