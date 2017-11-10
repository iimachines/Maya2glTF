#pragma once

#include "SceneTypes.h"
#include "MeshSetNames.h"

/** 
 * The indices to points, normals, etc for a single Maya mesh
 * Unlike a typical GPU mesh, DCC software like Maya has separate indices for each element semantic, e.g. to allow sharing points of sharp corners.
 */
class MeshIndices
{
public:
	MeshIndices(const MeshSetNames& setNames, const MFnMesh& fnMesh);
	~MeshIndices();

	const auto& indices(const Semantic::Kind semantic, const SetIndex setIndex ) const
	{
		return m_indexSets[semantic].at(setIndex);
	}

	// TODO: Support other primitives
	auto primitiveKind() const { return TRIANGLE_LIST; }
	size_t primitiveCount(const SetIndex setIndex) const { return indices(Semantic::POSITION, 0).size() / 3; }

	size_t shaderCount() const { return m_isShaderUsed.size(); }
	
	// Maps the index of each primitive to the single attached shader index.
	const auto& primitiveToShaderIndexMap() const { return m_primitiveToShaderIndexMap; }

	// Some primitives don't have a shader attached (e.g. primitives from blend-shape)
	bool isShaderUsedByAnyPrimitive(const int index) const { return m_isShaderUsed[index]; }

	void dump(const std::string& name, const std::string& indent) const;

private:
	std::array<std::map<SetIndex, IndexVector>, Semantic::COUNT> m_indexSets;

	IndexVector	m_primitiveToShaderIndexMap;

	std::vector<bool> m_isShaderUsed; 

	DISALLOW_COPY_AND_ASSIGN(MeshIndices);
};

