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
	assert(sizeof(S) % sizeof(T) == 0);

	if (span.empty())
		return gsl::span<T>();

	const S* bgn_ptr = &span[0];
	const S* end_ptr = bgn_ptr + span.size();

	return gsl::make_span(reinterpret_cast<const T*>(bgn_ptr), reinterpret_cast<const T*>(end_ptr));
}

