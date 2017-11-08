#pragma once

#include "SceneTypes.h"

class MeshIndices
{
public:
	MeshIndices(MFnMesh fnMesh);
	~MeshIndices();

	const auto& indices(const Semantic::Kind semantic) const { return m_indices[semantic]; }

	// TODO: Support other primitives
	auto primitiveKind() const { return TRIANGLE_LIST; }
	size_t primitiveCount() const { return indices(Semantic::POSITION).size() / 3; }

	size_t shaderCount() const { return m_isShaderUsed.size(); }
	
	// Maps the index of each primitive to the attached shader.
	const auto& primitiveToShaderIndexMap() const { return m_primitiveToShaderIndexMap; }

	// Some primitives don't have shaders attached (e.g. primitives from blend-shape)
	bool isShaderUsedByAnyPrimitive(const int index) const { return m_isShaderUsed[index]; }

	void dump(std::string name, std::string indent) const;

private:
	IndexVector	m_indices[Semantic::COUNT];

	IndexVector	m_primitiveToShaderIndexMap;

	std::vector<bool> m_isShaderUsed; 

	DISALLOW_COPY_AND_ASSIGN(MeshIndices);
};

