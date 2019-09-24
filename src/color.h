#pragma once

#include "basicTypes.h"

// Convert HSV in the range [0..1, 0..1, 0..1] to RGB in the same range.
Float3 hsvToRgb(const Float3 &hsv);

inline Float4 hsvToRgb(const Float3 &hsv, const float alpha) {
    const auto rgb = hsvToRgb(Float3({hsv[0], hsv[1], hsv[2]}));
    return {rgb[0], rgb[1], rgb[2], alpha};
}

// Convert HSV in the range [0..1, 0..1, 0..1] to RGB in the same range, keeping
// alpha
inline Float4 hsvToRgb(const Float4 &hsv) {
    const auto rgb = hsvToRgb(Float3({hsv[0], hsv[1], hsv[2]}));
    return {rgb[0], rgb[1], rgb[2], hsv[3]};
}
