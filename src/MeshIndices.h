#pragma once

#include "sceneTypes.h"
#include "MeshSemantics.h"

/** 
 * The per-primitive (e.g. triangle) indices to points, normals, etc for a single Maya mesh
 * Unlike a typical GPU mesh, DCC software like Maya has separate indices for each element semantic, e.g. to allow sharing points of sharp corners.
 */

typedef std::vector<IndexVector> ComponentIndicesPerSetIndex;
typedef std::array<ComponentIndicesPerSetIndex, Semantic::COUNT> ComponentIndicesPerSetIndexTable;
typedef std::vector<bool> ShaderUsageVector;

class MeshIndices
{
public:
	MeshIndices(const MeshSemantics& setNames, const MFnMesh& fnMesh);
	~MeshIndices();

	const ComponentIndicesPerSetIndexTable& table() const
	{
		return m_table;
	}

	// TODO: Support other primitives
	auto primitiveKind() const { return TRIANGLE_LIST; }
	size_t primitiveCount(const SetIndex setIndex) const { return m_table.at(Semantic::POSITION).at(0).size() / 3; }

	size_t shaderCount() const { return m_isShaderUsed.size(); }
	
	// Maps the index of each primitive to the single attached shader index.
	const auto& primitiveToShaderIndexMap() const { return m_primitiveToShaderIndexMap; }

	// Some primitives don't have a shader attached (e.g. primitives from blend-shape)
	const ShaderUsageVector& shaderUsages() const { return m_isShaderUsed; }

	const MObjectArray& shaderObjects() const { return m_shaders; }

	void dump(const std::string& name, const std::string& indent) const;

private:
	ComponentIndicesPerSetIndexTable m_table;

	MObjectArray m_shaders;
	IndexVector	m_primitiveToShaderIndexMap;

	std::vector<bool> m_isShaderUsed; 

	DISALLOW_COPY_AND_ASSIGN(MeshIndices);
};

