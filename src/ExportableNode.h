#pragma once

#include "ExportableItem.h"	
#include "ExportableMesh.h"

class ExportableNode : public ExportableItem
{
public:
	ExportableNode(MDagPath dagPath, MString name, ExportableResources& resources, const Arguments& args);
	~ExportableNode();

	static std::unique_ptr<ExportableNode> from(MDagPath dagPath, ExportableResources& resources, const Arguments& args);

	GLTF::Node glNode;

private:
	std::unique_ptr<ExportableMesh> m_mesh;

	GLTF::Node::TransformMatrix m_matrix;

	DISALLOW_COPY_AND_ASSIGN(ExportableNode);
};

