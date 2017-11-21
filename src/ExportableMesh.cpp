#include "externals.h"
#include "Mesh.h"
#include "ExportableMesh.h"
#include "ExportablePrimitive.h"
#include "Arguments.h"

ExportableMesh::ExportableMesh(const MDagPath& shapeDagPath, ExportableResources& resources, const Arguments& args)
{
	Mesh mayaMesh(shapeDagPath);

	if (args.dumpMaya)
	{
		mayaMesh.dump(shapeDagPath.fullPathName().asChar(), "");
	}

	const MeshShape& mainShape = mayaMesh.shape();
	const auto& renderables = mayaMesh.renderables();
	const auto& shadingMap = mainShape.indices().shadingPerInstance();
	const auto& shading = shadingMap.at(renderables.instanceIndex);

	for (auto && pair : renderables.table())
	{
		const auto& vertexSignature = pair.first;
		const auto& vertexBuffer = pair.second;

		auto& shaderGroup = shading.shaderGroups[vertexSignature.shaderIndex];
		auto exportablePrimitive = new ExportablePrimitive(vertexBuffer, shaderGroup, resources);
		m_primitives.emplace_back(exportablePrimitive);

		glMesh.primitives.push_back(&exportablePrimitive->glPrimitive);
	}
}

ExportableMesh::~ExportableMesh()
{
}
