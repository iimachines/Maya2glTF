#pragma once

#include "ExportableObject.h"	
#include "ExportableMesh.h"

class ExportableNode : public ExportableObject
{
public:
	ExportableNode(MDagPath dagPath, ExportableResources& resources);
	~ExportableNode();

	static std::unique_ptr<ExportableNode> from(MDagPath dagPath, ExportableResources& resources);

	std::unique_ptr<NodeAnimation> createAnimation(const int frameCount, const double scaleFactor) override;

	MDagPath dagPath;
	GLTF::Node glNode;

	const GLTF::Node::TransformTRS& transform() const { return m_transform; };

private:
	std::unique_ptr<ExportableMesh> m_mesh;

	GLTF::Node::TransformTRS m_transform;

	DISALLOW_COPY_AND_ASSIGN(ExportableNode);
};

