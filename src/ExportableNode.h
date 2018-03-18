#pragma once

#include "ExportableObject.h"	
#include "ExportableMesh.h"
#include "NodeHierarchy.h"

class ExportableNode : public ExportableObject
{
public:
	~ExportableNode();

	ExportableMesh* mesh() const { return m_mesh.get(); }

	MDagPath dagPath;
	GLTF::Node glNode;
	double scaleFactor;

	MDagPath parentDagPath;
	GLTF::Node::TransformTRS initialTransform;

	std::unique_ptr<NodeAnimation> createAnimation(const int frameCount, const double scaleFactor) override;

private:
	friend class NodeHierarchy;

	ExportableNode(NodeHierarchy& hierarchy, std::unique_ptr<ExportableNode>& owner, MDagPath dagPath);

	std::unique_ptr<ExportableMesh> m_mesh;

	DISALLOW_COPY_MOVE_ASSIGN(ExportableNode);
};

