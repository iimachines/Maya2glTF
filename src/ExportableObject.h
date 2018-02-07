#pragma once

#include "ExportableItem.h"

class Arguments;
class ExportableResources;

class ExportableObject : public ExportableItem
{
public:
	ExportableObject(MObject mObj);
	virtual ~ExportableObject() = 0;

	void handleNameAssignment(const Arguments& args, GLTF::Object& glObj);
	void handleNameAssignment(const ExportableResources& resources, GLTF::Object& glObj);

	const std::string& name() const { return _name; }

private:
	std::string _name;
};
