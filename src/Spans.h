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
	if (span.empty())
		return gsl::span<T>();

	const S& bgn = *span.begin();
	const S& end = *span.end();

	return gsl::make_span(reinterpret_cast<const T*>(&bgn), reinterpret_cast<const T*>(&end));
}

template<typename T, typename S>
static void dump_span(const std::string name, gsl::span<S> span, const std::string indent)
{
	auto components = reinterpret_span<T>(span);
	const size_t groupSize = sizeof(S) / sizeof(T);

	cout << indent << name << ": [ ";

	if (groupSize == 1)
	{
		auto separator = "";

		for (auto i = 0; i<components.size(); ++i)
		{
			cout << separator;
			cout << components[i];
			separator = ", ";
		}
	}
	else
	{
		auto groupSeparator = "";

		for (auto i = 0; i<components.size(); i += groupSize)
		{
			cout << groupSeparator;

			auto separator = "";
			for (auto j = 0; j<groupSize; ++j)
			{
				cout << separator;
				cout << components[i+j];
				separator = ",";
			}

			groupSeparator = ",  ";
		}
	}

	cout << "]";
}
