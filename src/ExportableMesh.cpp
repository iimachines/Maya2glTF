#include "externals.h"
#include "Mesh.h"
#include "ExportableMesh.h"
#include "ExportablePrimitive.h"
#include "ExportableResources.h"
#include "Arguments.h"

ExportableMesh::ExportableMesh(const MDagPath& shapeDagPath, ExportableResources& resources)
	: ExportableObject(shapeDagPath.node())
{
	handleNameAssignment(resources, glMesh);

	Mesh mayaMesh(shapeDagPath, resources.arguments());

	const Arguments& args = resources.arguments();

	if (args.dumpMaya)
	{
		mayaMesh.dump(*args.dumpMaya, shapeDagPath.fullPathName().asChar());
	}

	const MeshShape* mainShape = mayaMesh.shape();
	if (mainShape)
	{
		const auto& renderables = mayaMesh.renderables();
		const auto& shadingMap = mainShape->indices().shadingPerInstance();
		const auto& shading = shadingMap.at(renderables.instanceIndex);
		const int shaderCount = static_cast<int>(shading.shaderGroups.length());

		const auto& vertexBufferEntries = renderables.table();
		const size_t vertexBufferCount = vertexBufferEntries.size();
		size_t vertexBufferIndex = 0;
		for (auto && pair : vertexBufferEntries)
		{
			const auto& vertexSignature = pair.first;
			const auto& vertexBuffer = pair.second;

			const int shaderIndex = vertexSignature.shaderIndex;
			auto& shaderGroup = shaderIndex >= 0 && shaderIndex < shaderCount
				? shading.shaderGroups[shaderIndex]
				: MObject::kNullObj;

			auto exportablePrimitive = std::make_unique<ExportablePrimitive>(vertexBuffer, resources);

			// Assign material to primitive
			if (args.colorizeMaterials)
			{
				const float h = vertexBufferIndex * 1.0f / vertexBufferCount;
				const float s = shaderCount == 0 ? 0.5f : 1;
				const float v = shaderIndex < 0 ? 0.5f : 1;
				exportablePrimitive->glPrimitive.material = resources.getDebugMaterial({ h,s,v })->glMaterial();
			}
			else
			{
				auto material = resources.getMaterial(shaderGroup);
				if (!material && resources.arguments().defaultMaterial)
					material = resources.getDefaultMaterial();

				if (material)
					exportablePrimitive->glPrimitive.material = material->glMaterial();
			}

			glMesh.primitives.push_back(&exportablePrimitive->glPrimitive);

			m_primitives.emplace_back(move(exportablePrimitive));

			++vertexBufferIndex;
		}
	}
}

ExportableMesh::~ExportableMesh()
{
}
