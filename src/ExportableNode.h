#pragma once

#include "ExportableObject.h"	
#include "ExportableMesh.h"
#include "NodeHierarchy.h"

class ExportableNode : public ExportableObject
{
public:
	ExportableNode(MDagPath dagPath, ExportableResources& resources);
	~ExportableNode();

	// Phase 1
	static std::unique_ptr<ExportableNode> from(MDagPath dagPath, ExportableResources& resources);

	MDagPath dagPath;
	GLTF::Node glNode;
	double scaleFactor;

	// Phase 2
	void connectToHierarchy(const NodeHierarchy& hierarchy);

	MDagPath parentDagPath;
	GLTF::Node::TransformTRS transform;

	// Phase 3
	std::unique_ptr<NodeAnimation> createAnimation(const int frameCount, const double scaleFactor) override;

private:
	std::unique_ptr<ExportableMesh> m_mesh;

	DISALLOW_COPY_AND_ASSIGN(ExportableNode);
};

