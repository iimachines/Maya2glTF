#pragma once

#include "sceneTypes.h"
#include "MeshRenderables.h"
#include "ExportableMesh.h"

typedef std::vector<std::unique_ptr<GLTF::Accessor>> MeshAccessorPerSetIndex;
typedef std::array<MeshAccessorPerSetIndex, Semantic::COUNT> MeshAccessorPerSetIndexTable;

class ExportableResources;

class ExportablePrimitive
{
public:
	ExportablePrimitive(
		const VertexBuffer& vertexBuffer, 
		ExportableResources& resources);
	
	ExportablePrimitive(
		const VertexBuffer& vertexBuffer, 
		ExportableResources& resources,
		Semantic::Kind debugSemantic,
		int debugShapeIndex,
		double debugLineLength,
		Color debugLineColor);
	
	virtual ~ExportablePrimitive();

	GLTF::Primitive glPrimitive;
	std::unique_ptr<GLTF::Accessor> glIndices;
	MeshAccessorPerSetIndexTable glAccessorTable;

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportablePrimitive);
};
