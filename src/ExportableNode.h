#pragma once

#include "ExportableItem.h"	
#include "ExportableMesh.h"

class Arguments;

class ExportableNode : public ExportableItem
{
public:
	ExportableNode(MDagPath dagPath, MString name, const Arguments& args);
	~ExportableNode();

	static std::unique_ptr<ExportableNode> from(MDagPath dagPath, const Arguments& args);

	GLTF::Node glNode;

private:
	std::unique_ptr<ExportableMesh> m_mesh;

	DISALLOW_COPY_AND_ASSIGN(ExportableNode);
};

