#pragma once

#include "MeshShape.h"
#include "MeshBlendShapes.h"
#include "MeshRenderables.h"
#include "MeshShapeCollection.h"

class Mesh
{
public:
	Mesh(const MDagPath& dagPath);
	virtual ~Mesh();

	void dump(IndentableStream& cout, const std::string& name) const;

	const MeshShape* shape() const { return m_shape.get(); }

	/** null if the mesh has no blend-shapes */
	const MeshBlendShapes* blendShapes() const { return m_blendShapes.get(); }

	const MeshRenderables& renderables() const { return *m_renderables; }

private:
	static MObject tryExtractBlendController(const MFnMesh& fnMesh);

private:
	std::unique_ptr<MeshShape> m_shape;
	std::unique_ptr<MeshBlendShapes> m_blendShapes;
	std::unique_ptr<MeshShapeCollection> m_shapeCollection;
	std::unique_ptr<MeshRenderables> m_renderables;
};

