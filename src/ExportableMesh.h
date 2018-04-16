#pragma once

#include "basicTypes.h"
#include "ExportableObject.h"

class ExportableResources;
class ExportablePrimitive;
class Arguments;
class ExportableScene;
class ExportableNode;

class ExportableMesh : public ExportableObject
{
public:
	// TODO: Support instancing, for now we create a new mesh for each node.
	// To properly support instance, we need to decide what to do with shapes that are both with and without a skeleton 
	// Do we generate two meshes, with and without skinning vertex attributes?
	ExportableMesh(ExportableScene& scene, const MDagPath& shapeDagPath);
	virtual ~ExportableMesh();

	GLTF::Mesh glMesh;
	GLTF::Skin glSkin;

	MPoint pivotPoint;

	size_t blendShapeCount() const { return m_weightPlugs.size(); }

	gsl::span<const float> getInitialWeights() const { return m_initialWeights; }

	std::vector<float> getCurrentWeights() const;

	void setupNode(GLTF::Node& node);

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableMesh);

	std::vector<float> m_initialWeights;
	std::vector<MPlug> m_weightPlugs;
	std::vector<std::unique_ptr<ExportablePrimitive>> m_primitives;

	std::vector<Float4x4> m_inverseBindMatrices;
	std::unique_ptr<GLTF::Accessor> m_inverseBindMatricesAccessor;
};

