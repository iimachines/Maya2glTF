#pragma once
#include "ExportableObject.h"

class ExportableResources;
class ExportablePrimitive;
class Arguments;
class Mesh;

class ExportableMesh : public ExportableObject
{
public:
	ExportableMesh(const MDagPath& shapeDagPath, ExportableResources& resources);
	virtual ~ExportableMesh();

	GLTF::Mesh glMesh;

	size_t blendShapeCount() const { return m_weightPlugs.size(); }

	gsl::span<const float> getInitialWeights() const { return m_initialWeights; }

	std::vector<float> getCurrentWeights() const;


private:
	std::vector<float> m_initialWeights;
	std::vector<MPlug> m_weightPlugs;
	std::vector<std::unique_ptr<ExportablePrimitive>> m_primitives;
};

