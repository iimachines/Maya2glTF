#include "externals.h"
#include "ExportableItem.h"
#include "NodeAnimation.h"

ExportableItem::ExportableItem()
{
}

ExportableItem::~ExportableItem()
{
}

std::unique_ptr<NodeAnimation> ExportableItem::createAnimation(const int frameCount, const double scaleFactor)
{
	return nullptr;
}
