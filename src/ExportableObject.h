#pragma once

#include "ExportableItem.h"

class Arguments;
class ExportableResources;

class ExportableObject : public ExportableItem
{
public:
	ExportableObject(MObject mObj);
	virtual ~ExportableObject() = 0;

	const std::string& name() const { return _name; }

private:
	std::string _name;
};
