#pragma once

#include "ExportableObject.h"	
#include "ExportableMesh.h"

class ExportableNode : public ExportableObject
{
public:
	ExportableNode(MDagPath dagPath, ExportableResources& resources);
	~ExportableNode();

	static std::unique_ptr<ExportableNode> from(MDagPath dagPath, ExportableResources& resources);

	virtual std::unique_ptr<ExportableClip> createClip(const std::string& clipName, const int frameCount);

	MDagPath dagPath;
	GLTF::Node glNode;

private:
	std::unique_ptr<ExportableMesh> m_mesh;

	GLTF::Node::TransformTRS m_transform;

	DISALLOW_COPY_AND_ASSIGN(ExportableNode);
};

