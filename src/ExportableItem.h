#pragma once

#include "sceneTypes.h"

class ExportableItem
{
public:
	ExportableItem() {}
	virtual ~ExportableItem() = 0;

private:
	DISALLOW_COPY_AND_ASSIGN(ExportableItem);
};
