#pragma once

#include "sceneTypes.h"
#include "MeshRenderables.h"
#include "ExportableMesh.h"
#include "ExportableMaterial.h"

typedef std::vector<std::unique_ptr<GLTF::Primitive::Target>> BlendShapeToTargetTable;

class ExportableResources;

class ExportablePrimitive
{
public:
	ExportablePrimitive(
		const VertexBuffer& vertexBuffer,
		ExportableResources& resources,
		ExportableMaterial* material);
	
	ExportablePrimitive(
		const VertexBuffer& vertexBuffer, 
		ExportableResources& resources,
		Semantic::Kind debugSemantic,
		const ShapeIndex& debugShapeIndex,
		double debugLineLength,
		Color debugLineColor);
	
	virtual ~ExportablePrimitive();

	GLTF::Primitive glPrimitive;
	std::unique_ptr<GLTF::Accessor> glIndices;
	BlendShapeToTargetTable glTargetTable;

private:
	std::vector<std::unique_ptr<GLTF::Accessor>> glAccessors;

	DISALLOW_COPY_MOVE_ASSIGN(ExportablePrimitive);
};
