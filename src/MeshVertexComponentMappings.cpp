#include "externals.h"
#include "MeshIndices.h"
#include "MeshVertices.h"
#include "dump.h"
#include "MeshShape.h"
#include "MeshBlendShapes.h"
#include "MeshVertexComponentMappings.h"

MeshVertexComponentMappings::MeshVertexComponentMappings(
	const InstanceIndex instanceIndex,
	const MeshIndicesCollection& meshIndicesCollection)
	: instanceIndex(instanceIndex)
{
	MStatus status;

	const auto& meshIndices = meshShape.indices();

	const auto& indicesTable = meshIndices.table();
	const auto& verticesTable = meshVertices.table();

	auto& shadingPerInstance = meshIndices.shadingPerInstance();

	auto& shading = shadingPerInstance.at(instanceIndex);
	const auto shaderCount = shading.shaderCount();

	const auto primitiveCount = meshIndices.primitiveCount();
	const auto vertexCount = meshIndices.vertexCount();
	const auto perPrimitiveVertexCount = meshIndices.perPrimitiveVertexCount();

	auto signatureSize = meshSemantics.totalSetCount();

	const auto hasBlendShapes = maybeBlendShapes && !maybeBlendShapes->empty();

	// Verify that all blend-shapes have the same "topology"
	if (hasBlendShapes)
	{
		const auto baseShape = maybeBlendShapes->baseShape();
		if (baseShape->indices().vertexCount() != vertexCount)
			throw std::runtime_error(formatted("Base shape '%s' has different topology from '%s'!",
				meshShape.dagPath().fullPathName().asChar(), baseShape->dagPath().fullPathName().asChar()));

		for (auto&& entry : maybeBlendShapes->entries())
		{
			const auto& shape = entry->shape;
			if (shape.indices().vertexCount() != vertexCount)
				throw std::runtime_error(formatted("Blend shape '%s' has different topology from '%s'!",
					meshShape.dagPath().fullPathName().asChar(), shape.dagPath().fullPathName().asChar()));

			signatureSize += shape.semantics().totalSetCount();
		}
	}

	MeshVertexSignature signature;
	signature.reserve(signatureSize);

	auto primitiveVertexIndex = 0;

	for (auto primitiveIndex = 0; primitiveIndex < primitiveCount; ++primitiveIndex)
	{
		auto shaderIndex = shading.primitiveToShaderIndexMap[primitiveIndex];
		if (shaderIndex < 0)
			continue;

		// Determine signature (used semantics per shader)
		for (int counter = perPrimitiveVertexCount; --counter >= 0; ++primitiveVertexIndex)
		{
			signature.clear();

			for (auto && indicesPerSet : indicesTable)
			{
				for (auto && indices : indicesPerSet)
				{
					const auto index = indices[primitiveVertexIndex];
					signature.push_back(index >= 0);
				}
			}

			// Also add blend shapes indices to the signature. 
			// The topology of the blend shapes must be exactly the same as the main mesh, 
			// ie if we split a vertex in the main mesh, 
			// we must also split it in the blend shapes.
			if (hasBlendShapes)
			{
				const auto& entries = maybeBlendShapes->entries();
				for (auto&& entry : entries)
				{
					const auto& shape = entry->shape;

					for (auto && indicesPerSet : shape.indices().table())
					{
						for (auto && indices : indicesPerSet)
						{
							const auto index = indices[primitiveVertexIndex];
							signature.push_back(index >= 0);
						}
					}
				}
			}

			MeshVertexComponentIndices& componentIndices = m_table[signature];

			componentIndices.reserve(signatureSize);

			// Now register the indices used for the current vertex, but only when used.
			for (auto && indicesPerSet : indicesTable)
			{
				for (auto && indices : indicesPerSet)
				{
					const auto index = indices[primitiveVertexIndex];
					if (signature[index])
						signature.push_back(index >= 0);
				}
			}

			// Also add blend shapes indices to the signature. 
			// The topology of the blend shapes must be exactly the same as the main mesh, 
			// ie if we split a vertex in the main mesh, 
			// we must also split it in the blend shapes.
			if (hasBlendShapes)
			{
				const auto& entries = maybeBlendShapes->entries();
				for (auto&& entry : entries)
				{
					const auto& shape = entry->shape;

					for (auto && indicesPerSet : shape.indices().table())
					{
						for (auto && indices : indicesPerSet)
						{
							const auto index = indices[primitiveVertexIndex];
							indicesPerSignature.push_back(index);
							signature.push_back(index >= 0);
						}
					}
				}
			}

			componentIndices.insert(signature, indicesPerSignature);
		}
	}
}
