#pragma once

#include "MeshRenderable.h"
#include "MeshShape.h"
#include "MeshBlendShapes.h"

typedef std::vector<std::unique_ptr<MeshRenderable>> MeshRenderables;

class Mesh
{
public:
	Mesh(const MDagPath& dagPath);
	virtual ~Mesh();

	void dump(const std::string& name, const std::string& indent) const;

	const MeshShape& shape() const { return *m_shape; }
	
	/** null if the mesh has no blend-shapes */
	const MeshBlendShapes* blendShapes() const { return m_blendShapes.get(); }

	const MeshRenderables& renderables() const { return m_renderables; }

private:
	static MObject tryExtractBlendController(const MFnMesh& fnMesh);

private:
	std::unique_ptr<MeshShape> m_shape;
	std::unique_ptr<MeshBlendShapes> m_blendShapes;
	MeshRenderables m_renderables;
};

