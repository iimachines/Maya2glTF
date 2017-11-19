#pragma once

#include "sceneTypes.h"
#include "MeshSemantics.h"

/** 
 * The per-primitive (e.g. triangle) indices to points, normals, etc for a single Maya mesh
 * We call these vertex components, or just components.
 * Unlike a typical GPU mesh, DCC software like Maya has separate indices 
 * for each element semantic, e.g. to allow using a single point for a sharp corner
 */

// NOTE: Some components might have no indices for some semantics (UVs, color, tangent).
// In this case, NoIndex (-1) is used.
//
// When splitting a mesh into renderable parts, 
// we determine what semantics are actually used 
const Index NoIndex = -1;

typedef std::vector<IndexVector> VertexComponentIndicesPerSetIndex;
typedef std::array<VertexComponentIndicesPerSetIndex, Semantic::COUNT> VertexComponentIndicesPerSetIndexTable;
typedef std::vector<bool> ShaderUsageVector;

struct MeshShading
{
	MObjectArray shaderGroups;

	// Maps the index of each primitive to the single attached shader index.
	IndexVector primitiveToShaderIndexMap;

	// Some primitives don't have a shader attached (e.g. primitives from blend-shape)
	ShaderUsageVector isShaderUsed;

	size_t shaderCount() const { return isShaderUsed.size(); }
};

typedef std::map<InstanceIndex, MeshShading> MeshShadingPerInstance;

class MeshIndices
{
public:
	MeshIndices(const MeshSemantics& setNames, const MFnMesh& fnMesh);
	virtual ~MeshIndices();

	const VertexComponentIndicesPerSetIndexTable& table() const
	{
		return m_table;
	}

	std::string meshName;

	// TODO: Support other primitives
	auto primitiveKind() const { return TRIANGLE_LIST; }
	auto perPrimitiveVertexCount() const { return 3; }
	auto primitiveCount() const { return m_table.at(Semantic::POSITION).at(0).size() / perPrimitiveVertexCount(); }
	auto vertexCount() const { return perPrimitiveVertexCount() * primitiveCount(); }

	auto indexAt(const size_t semanticIndex, const size_t setIndex) const
	{
		return m_table.at(semanticIndex).at(setIndex);
	}

	const auto& shadingPerInstance() const { return m_shadingPerInstance; }

	void dump(const std::string& name, const std::string& indent) const;

private:
	VertexComponentIndicesPerSetIndexTable m_table;
	MeshShadingPerInstance m_shadingPerInstance;

	DISALLOW_COPY_AND_ASSIGN(MeshIndices);
};

