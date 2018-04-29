#pragma once

#include "macros.h"

class ExportableFrames;
class NodeAnimation;

class ExportableItem
{
public:
	virtual ~ExportableItem() = 0;

	virtual std::unique_ptr<NodeAnimation> createAnimation(const ExportableFrames& frameTimes, const double scaleFactor);

protected:
	ExportableItem() = default;

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableItem);
};
