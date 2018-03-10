#pragma once

#include "macros.h"
#include "sceneTypes.h"
#include "MeshSemantics.h"

/** 
 * The per-primitive (e.g. triangle) indices to points, normals, etc for a single Maya mesh
 * We call these vertex elements, or just elements.
 * We use the word 'component' to indicate the coordinate of a point, vector or color.
 * Unlike a typical GPU mesh, DCC software like Maya has separate indices 
 * for each element semantic, e.g. to allow using a single point for a sharp corner
 */

// NOTE: Some elements might have no indices for some semantics (UVs, color, tangent).
// In this case, NoIndex (-1) is used.
//
// When splitting a mesh into renderable parts, 
// we determine what semantics are actually used 
const Index NoIndex = -1;

typedef std::vector<IndexVector> VertexElementIndicesPerSetIndex;
typedef std::array<VertexElementIndicesPerSetIndex, Semantic::COUNT> VertexElementIndicesPerSetIndexTable;
typedef std::vector<bool> ShaderUsageVector;

// Maya face index
typedef int FaceIndex;
typedef int TriangleIndex;
typedef std::vector<FaceIndex> TriangleToFaceIndexMap;

struct MeshShading
{
	MObjectArray shaderGroups;

	// Maps the index of each primitive to the single attached shader index.
	IndexVector primitiveToShaderIndexMap;
};

typedef std::map<InstanceIndex, MeshShading> MeshShadingPerInstance;

class MeshIndices
{
public:
	MeshIndices(const MeshSemantics* meshSemantics, const MFnMesh& fnMesh);
	virtual ~MeshIndices();

	const VertexElementIndicesPerSetIndexTable& table() const
	{
		return m_table;
	}

	const std::string meshName;
	const MeshSemantics& semantics;

	// TODO: Support other primitives
	PrimitiveKind primitiveKind() const { return TRIANGLE_LIST; }
	int perPrimitiveVertexCount() const { return 3; }
	int primitiveCount() const { return m_TriangleCount; }
	int maxVertexCount() const { return perPrimitiveVertexCount() * primitiveCount(); }

	const IndexVector& indicesAt(const size_t semanticIndex, const size_t setIndex) const
	{
		return m_table.at(semanticIndex).at(setIndex);
	}

	FaceIndex triangleToFaceIndex(TriangleIndex triangleIndex) const
	{
		return m_triangleToFaceIndexMap.at(triangleIndex);
	}

	const MeshShadingPerInstance& shadingPerInstance() const { return m_shadingPerInstance; }

	void dump(class IndentableStream& cout, const std::string& name) const;

private:
	int m_TriangleCount;
	VertexElementIndicesPerSetIndexTable m_table;
	MeshShadingPerInstance m_shadingPerInstance;
	TriangleToFaceIndexMap m_triangleToFaceIndexMap;

	DISALLOW_COPY_MOVE_ASSIGN(MeshIndices);
};

