#pragma once

#include "SceneTypes.h"
#include "MeshRenderables.h"
#include "ExportableMesh.h"

typedef std::vector<std::unique_ptr<GLTF::Accessor>> MeshAccessorPerSetIndex;
typedef std::array<MeshAccessorPerSetIndex, Semantic::COUNT> MeshAccessorPerSetIndexTable;

class ExportableResources;

class ExportablePrimitive
{
public:
	ExportablePrimitive(const VertexBuffer& vertexBuffer, ExportableResources& resources);
	virtual ~ExportablePrimitive();

	GLTF::Primitive glPrimitive;
	std::unique_ptr<GLTF::Accessor> glIndices;
	MeshAccessorPerSetIndexTable glAccessorTable;

private:
	std::vector<uint8> m_data;

	std::unique_ptr<GLTF::Accessor> createAccessor(
		const Semantic::Kind semantic, 
		const int offset, 
		const int count);
};
