#pragma once

#include "ExportableItem.h"	
#include "ExportableMesh.h"

class ExportableNode : public ExportableItem
{
public:
	ExportableNode(MDagPath dagPath, MString name);
	~ExportableNode();

	static std::unique_ptr<ExportableNode> from(MDagPath dagPath);

	GLTF::Node glNode;

private:
	std::unique_ptr<ExportableMesh> m_mesh;

	DISALLOW_COPY_AND_ASSIGN(ExportableNode);
};

