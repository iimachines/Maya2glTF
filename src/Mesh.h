#pragma once

#include "MeshShape.h"

class Arguments;

typedef std::vector<std::unique_ptr<MeshShape>> MeshShapes;

class Mesh
{
public:
	Mesh(const MDagPath& dagPath, const Arguments& args);
	~Mesh();

	void dump(IndentableStream& out, const std::string& name) const;

	bool isEmpty() const { return m_shapes.empty(); }

	const MeshShape& shape() const { return *m_shapes.at(0); }

	const MeshShapes& shapes() const { return m_shapes; }

private:
	DISALLOW_COPY_MOVE_ASSIGN(Mesh);

	struct Cleanup
	{
		~Cleanup();
		MObject tempOutputMesh;
	};

	MeshShapes m_shapes;
	Cleanup m_cleanup;

	MObject getOrCreateOutputShape(MPlug& outputGeometryPlug, MObject& createdMesh) const;

	static MObject tryExtractBlendShapeDeformer(const MFnMesh& fnMesh, const MSelectionList& ignoredDeformers);
};

