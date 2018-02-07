#pragma once

#include "ExportableObject.h"	
#include "ExportableMesh.h"

class ExportableNode : public ExportableObject
{
public:
	ExportableNode(MDagPath dagPath, ExportableResources& resources);
	~ExportableNode();

	static std::unique_ptr<ExportableNode> from(MDagPath dagPath, ExportableResources& resources);

	GLTF::Node glNode;

private:
	std::unique_ptr<ExportableMesh> m_mesh;

	GLTF::Node::TransformMatrix m_matrix;

	DISALLOW_COPY_AND_ASSIGN(ExportableNode);
};

