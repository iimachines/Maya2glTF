#pragma once

#include "basicTypes.h"
#include "spans.h"

struct CollectionHashers
{
	std::size_t operator()(const gsl::span<int>& vec) const
	{
		return hash_value(reinterpret_span<uint32_t>(vec));
	}

	std::size_t operator()(const gsl::span<float>& vec) const
	{
		return hash_value(reinterpret_span<uint32_t>(vec));
	}

	std::size_t operator()(const std::vector<int>& vec) const
	{
		return hash_value(reinterpret_span<uint32_t>(span(vec)));
	}

	std::size_t operator()(const std::vector<float>& vec) const
	{
		return hash_value(reinterpret_span<uint32_t>(span(vec)));
	}
};

