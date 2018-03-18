#pragma once

template<typename T>
static gsl::span<const T> span(const std::vector<T>& vec)
{
	return gsl::make_span(vec);
}

static gsl::span<const MFloatPoint> span(const MFloatPointArray& marray)
{
	return marray.length() > 0 ? gsl::make_span(&marray[0], marray.length()) : gsl::span<const MFloatPoint>();
}

static gsl::span<const MFloatVector> span(const MFloatVectorArray& marray)
{
	return marray.length() > 0 ? gsl::make_span(&marray[0], marray.length()) : gsl::span<const MFloatVector>();
}

static gsl::span<const MColor> span(const MColorArray& marray)
{
	return marray.length() > 0 ? gsl::make_span(&marray[0], marray.length()) : gsl::span<const MColor>();
}

template<typename T, typename S>
static gsl::span<const T> reinterpret_span(const gsl::span<S>& span)
{
	assert(sizeof(S) >= sizeof(T) ? sizeof(S) % sizeof(T) == 0 : sizeof(T) % sizeof(S) == 0);

	if (span.empty())
		return gsl::span<T>();

	const S* bgn_ptr = &span[0];
	const S* end_ptr = bgn_ptr + span.size();

	return gsl::make_span(reinterpret_cast<const T*>(bgn_ptr), reinterpret_cast<const T*>(end_ptr));
}

template<typename T, typename S>
static gsl::span<const T> reinterpret_span(const std::vector<S>& data)
{
	return reinterpret_span<T>(gsl::make_span(data));
}

template<typename T>
static gsl::span<T> mutable_span(const gsl::span<const T>& span)
{
	const T* bgn_ptr = &span[0];
	const T* end_ptr = bgn_ptr + span.size();
	return gsl::make_span(const_cast<T*>(bgn_ptr), const_cast<T*>(end_ptr));
}

static std::size_t hash_value(const gsl::span<const uint16_t>& span)
{
	std::size_t seed = span.size();
	for (const size_t i : span) {
		seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	return seed;
}

template<typename T>
static void reinterpret_span(const std::vector<gsl::span<T>>& vec) = delete;

template<typename T>
static void reinterpret_span(const gsl::span<gsl::span<T>>& vec) = delete;

template<typename T>
static void span(const std::vector<gsl::span<T>>& vec) = delete;

template<typename T>
static void span(const gsl::span<gsl::span<T>>& vec) = delete;

