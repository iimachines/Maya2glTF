#pragma once
#include "ExportableObject.h"

class ExportableResources;
class ExportablePrimitive;
class Arguments;
class Mesh;
class ExportableScene;

class ExportableMesh : public ExportableObject
{
public:
	ExportableMesh(ExportableScene& scene, const MDagPath& shapeDagPath);
	virtual ~ExportableMesh();

	GLTF::Mesh glMesh;
	GLTF::Skin glSkin;

	size_t blendShapeCount() const { return m_weightPlugs.size(); }

	gsl::span<const float> getInitialWeights() const { return m_initialWeights; }

	std::vector<float> getCurrentWeights() const;


private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableMesh);

	std::vector<float> m_initialWeights;
	std::vector<MPlug> m_weightPlugs;
	std::vector<std::unique_ptr<ExportablePrimitive>> m_primitives;
};

