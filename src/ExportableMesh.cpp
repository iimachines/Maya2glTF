#include "externals.h"
#include "Mesh.h"
#include "MeshSkeleton.h"
#include "ExportableMesh.h"
#include "ExportablePrimitive.h"
#include "ExportableResources.h"
#include "Arguments.h"
#include "MayaException.h"
#include "ExportableScene.h"
#include "ExportableNode.h"
#include "accessors.h"

ExportableMesh::ExportableMesh(
	ExportableScene& scene, 
	ExportableNode& node,
	const MDagPath& shapeDagPath)
	: ExportableObject(shapeDagPath.node())
{
	MStatus status;

	const std::string shapeName{ shapeDagPath.partialPathName(&status).asChar() };

	auto& resources = scene.resources();
	auto& args = resources.arguments();

	const auto mayaMesh = std::make_unique<Mesh>(scene, shapeDagPath, node);

	if (args.dumpMaya)
	{
		mayaMesh->dump(*args.dumpMaya, shapeDagPath.fullPathName().asChar());
	}

	if (!mayaMesh->isEmpty())
	{
		args.assignName(glMesh, shapeName);

		auto& mainShape = mayaMesh->shape();

		// Generate primitives
		MeshRenderables renderables(mayaMesh->allShapes(), args);
		const auto& shadingMap = mainShape.indices().shadingPerInstance();
		const auto& shading = shadingMap.at(renderables.instanceNumber);
		const auto shaderCount = static_cast<int>(shading.shaderGroups.length());

		const auto& vertexBufferEntries = renderables.table();
		const size_t vertexBufferCount = vertexBufferEntries.size();
		{
			size_t vertexBufferIndex = 0;
			for (auto && pair : vertexBufferEntries)
			{
				const auto& vertexSignature = pair.first;
				const auto& vertexBuffer = pair.second;

				const int shaderIndex = vertexSignature.shaderIndex;
				auto& shaderGroup = shaderIndex >= 0 && shaderIndex < shaderCount
					? shading.shaderGroups[shaderIndex]
					: MObject::kNullObj;


				ExportableMaterial* material = nullptr;

				// Assign material to primitive
				if (args.colorizeMaterials)
				{
					const float h = vertexBufferIndex * 1.0f / vertexBufferCount;
					const float s = shaderCount == 0 ? 0.5f : 1;
					const float v = shaderIndex < 0 ? 0.5f : 1;
					material = resources.getDebugMaterial({ h,s,v });
					++vertexBufferIndex;
				}
				else
				{
					material = resources.getMaterial(shaderGroup);
					if (!material && resources.arguments().defaultMaterial)
						material = resources.getDefaultMaterial();
				}

				if (material)
				{
					auto exportablePrimitive = std::make_unique<ExportablePrimitive>(vertexBuffer, resources, material);

					glMesh.primitives.push_back(&exportablePrimitive->glPrimitive);

					m_primitives.emplace_back(std::move(exportablePrimitive));

					if (args.debugTangentVectors)
					{
						auto debugPrimitive = std::make_unique<ExportablePrimitive>(
							vertexBuffer, resources, Semantic::Kind::TANGENT, ShapeIndex::main(), args.debugVectorLength, Color({ 1,0,0,1 }));
						glMesh.primitives.push_back(&debugPrimitive->glPrimitive);
						m_primitives.emplace_back(move(debugPrimitive));
					}

					if (args.debugNormalVectors)
					{
						auto debugPrimitive = std::make_unique<ExportablePrimitive>(
							vertexBuffer, resources, Semantic::Kind::NORMAL, ShapeIndex::main(), args.debugVectorLength, Color({ 1,1,0,1 }));
						glMesh.primitives.push_back(&debugPrimitive->glPrimitive);
						m_primitives.emplace_back(move(debugPrimitive));
					}
				}
			}

			for (auto&& shape: mayaMesh->allShapes())
			{
				if (shape->shapeIndex.isBlendShapeIndex())
				{
					m_weightPlugs.emplace_back(shape->weightPlug);
					m_initialWeights.emplace_back(shape->initialWeight);
					glMesh.weights.emplace_back(shape->initialWeight);
				}
			}
		}

		// Generate skin
		auto& skeleton = mainShape.skeleton();
		if (!skeleton.isEmpty())
		{
			args.assignName(glSkin, shapeName);

			auto& joints = skeleton.joints();

			std::map<int, std::vector<ExportableNode*>> distanceToRootMap;

			m_inverseBindMatrices.reserve(joints.size());

			// Get joints, and build inverse bind matrices.
			for (auto& joint: joints)
			{
				auto* jointNode = joint.node;
				glSkin.joints.emplace_back(const_cast<GLTF::Node*>(&jointNode->glPrimaryNode()));
				
				auto distanceToRoot = ExportableScene::distanceToRoot(jointNode->dagPath);
				distanceToRootMap[distanceToRoot].emplace_back(jointNode);

				Float4x4 inverseBindMatrix;
				joint.inverseBindMatrix.get(reinterpret_cast<float(&)[4][4]>(inverseBindMatrix));

				m_inverseBindMatrices.emplace_back(inverseBindMatrix);
			}

			m_inverseBindMatricesAccessor = contiguousChannelAccessor(
				shapeName + "/B",
				reinterpret_span<float>(m_inverseBindMatrices),
				16);

			glSkin.inverseBindMatrices = m_inverseBindMatricesAccessor.get();

			// Find root
			// NOTE: Disabled to support skeletons with multiple roots, the skeleton property is optional anyway
			//const auto& roots = distanceToRootMap.begin()->second;

			//if (roots.size() > 1)
			//{
			//	MayaException::printError(
			//		formatted("Skeletons with multiple roots are not yet supported, mesh '%s'", shapeName.c_str()));
			//}

			//auto rootJointNode = roots.at(0);
			//cout << prefix << "Using joint " << quoted(rootJointNode->name(), '\'') << " as skeleton root for mesh " << quoted(shapeName, '\'') << endl;
			//glSkin.skeleton = &rootJointNode->glPrimaryNode();
		}
	}
}

ExportableMesh::~ExportableMesh() = default;

void ExportableMesh::getAllAccessors(std::vector<GLTF::Accessor*>& accessors) const
{
    for (auto&& primitive : m_primitives)
    {
        primitive->getAllAccessors(accessors);
    }

    if (m_inverseBindMatricesAccessor)
    {
        accessors.emplace_back(m_inverseBindMatricesAccessor.get());
    }
}

std::vector<float> ExportableMesh::currentWeights() const
{
	std::vector<float> weights;
	weights.reserve(m_weightPlugs.size());

	for(auto& plug: m_weightPlugs)
	{
		float weight;
		THROW_ON_FAILURE(plug.getValue(weight));
		weights.emplace_back(weight);
	}

	return weights;
}

void ExportableMesh::setupNode(GLTF::Node& node)
{
	node.mesh = &glMesh;

	if (glSkin.inverseBindMatrices)
	{
		node.skin = &glSkin;
	}
}

void ExportableMesh::updateWeights()
{
	for (size_t i=0; i<m_weightPlugs.size(); ++i)
	{
		auto& plug = m_weightPlugs.at(i);
		auto& weight = glMesh.weights.at(i);
		THROW_ON_FAILURE(plug.getValue(weight));
	}
}
