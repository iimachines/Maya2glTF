#pragma once

#include "SceneTypes.h"

class MeshIndices
{
public:
	MeshIndices(MFnMesh fnMesh);
	~MeshIndices();

	const auto& indices(const Semantic semantic) const { return m_indices[semantic]; }

	// TODO: Support other primitives
	auto primitiveKind() const { return TRIANGLE_LIST; }
	size_t primitiveCount() const { return indices(POSITION).size() / 3; }

	size_t shaderCount() const { return m_isShaderUsed.size(); }
	const auto& shaderIndices() const { return m_primitiveToShaderIndexMap; }

	bool isSharedUsed(const int index) const { return m_isShaderUsed[index]; }

private:
	IndexVector	m_indices[NUM_SEMANTICS];

	// Maps the index of each primitive to the attached shader.
	IndexVector	m_primitiveToShaderIndexMap;

	// Some primitives don't have shaders attached (e.g. primitives from blend-shape)
	std::vector<bool> m_isShaderUsed; 
};

