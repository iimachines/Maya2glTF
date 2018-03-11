#include "externals.h"
#include "MeshShape.h"
#include "IndentableStream.h"
#include "Arguments.h"
#include "MayaException.h"
#include "DagHelper.h"

inline float getWeightValue(MPlug plug)
{
	float value;
	auto status = plug.getValue(value);
	return status.error() ? FP_NAN : value;
}

MeshShape::MeshShape(const MFnMesh& fnMesh, const Arguments& args, ShapeIndex shapeIndex, const MPlug& weightPlug) 
: shapeIndex(shapeIndex)
, weightPlug(weightPlug)
, initialWeight(getWeightValue(weightPlug))
{
	CONSTRUCTOR_BEGIN();
	m_semantics = std::make_unique<MeshSemantics>(fnMesh);
	m_indices = std::make_unique<MeshIndices>(m_semantics.get(), fnMesh);
	m_vertices = std::make_unique<MeshVertices>(*m_indices, fnMesh, shapeIndex, args);
	CONSTRUCTOR_END();
}

void MeshShape::dump(IndentableStream& out, const std::string& name) const
{
	out << quoted(name) << ": {" << endl << indent;

	m_semantics->dump(out, "semantics");
	out << "," << endl;
	m_vertices->dump(out, "vertices");
	out << "," << endl;
	m_indices->dump(out, "indices");

	out << endl << undent << '}' << endl;
}
