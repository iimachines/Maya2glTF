#pragma once

#include "MeshSemantics.h"
#include "MeshVertices.h"
#include "MeshIndices.h"
#include "MayaException.h"

class MeshShape
{
public:
	MeshShape(const MFnMesh& fnMesh, const Arguments& args, ShapeIndex shapeIndex, const MPlug& weightPlug, float initialWeight);
	virtual ~MeshShape();

	void dump(class IndentableStream& out, const std::string& name) const;

	const ShapeIndex shapeIndex; 
	const MPlug weightPlug; // isNull of main shape
	const float initialWeight = 0; 

	const MDagPath& dagPath() const { return m_dagPath; }
	const MeshSemantics& semantics() const { return *m_semantics; }
	const MeshVertices& vertices() const { return *m_vertices; }
	const MeshIndices& indices() const { return *m_indices; }

	size_t instanceNumber() const
	{
		MStatus status;
		const auto instanceNumber = m_dagPath.instanceNumber(&status);
		THROW_ON_FAILURE(status);
		return instanceNumber;
	}

private:
	MDagPath m_dagPath;

	std::unique_ptr<MeshSemantics> m_semantics;
	std::unique_ptr<MeshVertices> m_vertices;
	std::unique_ptr<MeshIndices> m_indices;

	DISALLOW_COPY_MOVE_ASSIGN(MeshShape);
};

