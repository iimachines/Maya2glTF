#pragma once

#include "ExportableItem.h"

class Arguments;
class ExportableResources;

class ExportableObject : public ExportableItem
{
public:
	ExportableObject(MObject mObj);
	virtual ~ExportableObject() = 0;

	const std::string& name() const { return m_name; }

	const MObject obj;

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableObject);

	std::string m_name;
};
