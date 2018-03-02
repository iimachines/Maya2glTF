#include "externals.h"
#include "ExportableItem.h"
#include "ExportableClip.h"

ExportableItem::ExportableItem()
{
}

ExportableItem::~ExportableItem()
{
}

std::unique_ptr<ExportableClip> ExportableItem::createClip(const std::string& clipName, const int frameCount)
{
	return nullptr;
}
