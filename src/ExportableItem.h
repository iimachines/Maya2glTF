#pragma once

#include "macros.h"

class ExportableFrames;
class NodeAnimation;
class Arguments;

class ExportableItem {
  public:
    virtual ~ExportableItem() = 0;

    virtual std::unique_ptr<NodeAnimation> createAnimation(const Arguments &args, const ExportableFrames &frameTimes,
                                                           double scaleFactor);

  protected:
    ExportableItem() = default;

  private:
    DISALLOW_COPY_MOVE_ASSIGN(ExportableItem);
};
