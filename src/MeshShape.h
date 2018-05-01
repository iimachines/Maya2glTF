#pragma once

#include "MeshSemantics.h"
#include "MeshVertices.h"
#include "MeshIndices.h"
#include "MayaException.h"

class ExportableNode;
class ExportableScene;

class MeshShape
{
public:
	MeshShape(const MeshIndices& mainIndices, const MFnMesh& fnMesh, const ExportableNode& node, const Arguments& args, ShapeIndex shapeIndex, const MPlug& weightPlug, float initialWeight);
	virtual ~MeshShape();

	virtual void dump(class IndentableStream& out, const std::string& name) const;

	const ShapeIndex shapeIndex; 
	const MPlug weightPlug; // isNull of main shape
	const float initialWeight = 0; 

	const MDagPath& dagPath() const { return m_dagPath; }
	const MeshSemantics& semantics() const { return *m_semantics; }
	const MeshVertices& vertices() const { return *m_vertices; }

	size_t instanceNumber() const;

protected:
	MeshShape(ShapeIndex shapeIndex);

	MDagPath m_dagPath;

	std::unique_ptr<MeshSemantics> m_semantics;
	std::unique_ptr<MeshVertices> m_vertices;

	DISALLOW_COPY_MOVE_ASSIGN(MeshShape);
};

class MainShape : public MeshShape
{
public:
	MainShape(ExportableScene& scene, const MFnMesh& fnMesh, const ExportableNode& node, ShapeIndex shapeIndex);
	virtual ~MainShape();

	const MeshIndices& indices() const { return *m_indices; }
	const MeshSkeleton& skeleton() const { return *m_skeleton; }

	void dump(class IndentableStream& out, const std::string& name) const override;

private:
	std::unique_ptr<MeshSkeleton> m_skeleton;
	std::unique_ptr<MeshIndices> m_indices;
	DISALLOW_COPY_MOVE_ASSIGN(MainShape);
};
