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
	const MDagPath& shapeDagPath)
	: ExportableObject(shapeDagPath.node())
{
	MStatus status;

	const std::string shapeName{ shapeDagPath.partialPathName(&status).asChar() };

	auto& resources = scene.resources();
	auto& args = resources.arguments();

	const auto mayaMesh = std::make_unique<Mesh>(scene, shapeDagPath);

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

				++vertexBufferIndex;
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
				glSkin.joints.emplace_back(&jointNode->glNode);
				
				auto distanceToRoot = ExportableScene::distanceToRoot(jointNode->dagPath);
				distanceToRootMap[distanceToRoot].emplace_back(jointNode);

				Float4x4 inverseBindMatrix;
				joint.inverseBindMatrix.get(reinterpret_cast<float(&)[4][4]>(inverseBindMatrix));

				m_inverseBindMatrices.emplace_back(inverseBindMatrix);
			}

			m_inverseBindMatricesAccessor = contiguousChannelAccessor(
				shapeName + "_ibm",
				reinterpret_span<float>(m_inverseBindMatrices),
				16);

			glSkin.inverseBindMatrices = m_inverseBindMatricesAccessor.get();

			// Find root
			const auto& roots = distanceToRootMap.begin()->second;

			if (roots.size() > 1)
			{
				MayaException::printError(
					formatted("Skeletons with multiple roots are not yet supported, mesh '%s'", shapeName.c_str()));
			}

			auto rootJointNode = roots.at(0);
			cout << prefix << "Using joint " << quoted(rootJointNode->name(), '\'') << " as skeleton root for mesh " << quoted(shapeName, '\'') << endl;
			glSkin.skeleton = &rootJointNode->glNode;
		}

		// Add pivot node, if needed
		const auto pivotPoint = mainShape.vertices().pivotPoint();
		if (pivotPoint != MPoint::origin)
		{
			// TODO: Can we use the pivot node of other stuff?
			m_pivotTransform.scale[0] = 1;
			m_pivotTransform.scale[1] = 1;
			m_pivotTransform.scale[2] = 1;

			m_pivotTransform.rotation[0] = 0;
			m_pivotTransform.rotation[1] = 0;
			m_pivotTransform.rotation[2] = 0;
			m_pivotTransform.rotation[3] = 1;

			m_pivotTransform.translation[0] = float(pivotPoint.x);
			m_pivotTransform.translation[1] = float(pivotPoint.y);
			m_pivotTransform.translation[2] = float(pivotPoint.z);

			glPivotNode = std::make_unique<GLTF::Node>();
			glPivotNode->transform = &m_pivotTransform;

			args.assignName(*glPivotNode, shapeName+":pivot");

			setupNode(*glPivotNode);
		}
	}
}

ExportableMesh::~ExportableMesh() = default;

std::vector<float> ExportableMesh::getCurrentWeights() const
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

	if (glSkin.skeleton)
	{
		node.skin = &glSkin;
	}
}
