#pragma once

#include "basicTypes.h"
#include "spans.h"

struct CollectionHashers {
    std::size_t operator()(const gsl::span<int> &vec) const {
        return hash_value(reinterpret_span<ushort>(vec));
    }

    std::size_t operator()(const gsl::span<float> &vec) const {
        return hash_value(reinterpret_span<ushort>(vec));
    }

    std::size_t operator()(const std::vector<int> &vec) const {
        return hash_value(reinterpret_span<ushort>(span(vec)));
    }

    std::size_t operator()(const std::vector<float> &vec) const {
        return hash_value(reinterpret_span<ushort>(span(vec)));
    }
};
