#include "externals.h"
#include "MeshShape.h"
#include "IndentableStream.h"
#include "Arguments.h"
#include "MeshSkeleton.h"
#include "NodeHierarchy.h"

MeshShape::MeshShape(ShapeIndex shapeIndex)
	: shapeIndex(shapeIndex)
{
}

MeshShape::MeshShape(const MeshIndices& mainIndices, const MFnMesh& fnMesh, const Arguments& args, ShapeIndex shapeIndex, const MPlug& weightPlug, const float initialWeight)
	: shapeIndex(shapeIndex)
	, weightPlug(weightPlug)
	, initialWeight(initialWeight)
{
	m_semantics = std::make_unique<MeshSemantics>(fnMesh, nullptr);
	m_vertices = std::make_unique<MeshVertices>(mainIndices, nullptr, fnMesh, shapeIndex, args);
}

MeshShape::~MeshShape() = default;

void MeshShape::dump(IndentableStream& out, const std::string& name) const
{
	out << quoted(name) << ": {" << endl << indent;

	m_semantics->dump(out, "semantics");
	out << "," << endl;
	m_vertices->dump(out, "vertices");

	out << endl << undent << '}' << endl;
}

MainShape::MainShape(NodeHierarchy& hierarchy, const MFnMesh& fnMesh, ShapeIndex shapeIndex) : MeshShape(shapeIndex)
{
	m_skeleton = std::make_unique<MeshSkeleton>(hierarchy, fnMesh);
	m_semantics = std::make_unique<MeshSemantics>(fnMesh, m_skeleton.get());
	m_indices = std::make_unique<MeshIndices>(m_semantics.get(), fnMesh);
	m_vertices = std::make_unique<MeshVertices>(*m_indices, m_skeleton.get(), fnMesh, shapeIndex, hierarchy.arguments());
}

MainShape::~MainShape() = default;

void MainShape::dump(IndentableStream& out, const std::string& name) const
{
	out << quoted(name) << ": {" << endl << indent;

	m_semantics->dump(out, "semantics");
	out << "," << endl;
	m_vertices->dump(out, "vertices");
	out << "," << endl;
	m_indices->dump(out, "indices");
	out << "," << endl;
	m_skeleton->dump(out, "skeleton");

	out << endl << undent << '}' << endl;
}


