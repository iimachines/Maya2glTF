#include "externals.h"

#include "ExportableItem.h"
#include "NodeAnimation.h"

ExportableItem::~ExportableItem() = default;

std::unique_ptr<NodeAnimation>
ExportableItem::createAnimation(const Arguments &, const ExportableFrames &, double ) {
    return nullptr;
}
