#pragma once

#include "ExportableObject.h"	
#include "ExportableMesh.h"
#include "ExportableScene.h"

class ExportableNode : public ExportableObject
{
public:
	~ExportableNode();
	
	ExportableMesh* mesh() const { return m_mesh.get(); }

	MDagPath dagPath;
	GLTF::Node glNode;
	double scaleFactor;

	MDagPath parentDagPath;

	MPoint pivotPoint;
	MMatrix pivotTransform;

	GLTF::Node::TransformTRS initialTransform;

	std::unique_ptr<NodeAnimation> createAnimation(const int frameCount, const double scaleFactor) override;

private:
	friend class ExportableScene;

	ExportableNode(MDagPath dagPath);

	void load(ExportableScene& scene);

	std::unique_ptr<ExportableMesh> m_mesh;

	DISALLOW_COPY_MOVE_ASSIGN(ExportableNode);
};

