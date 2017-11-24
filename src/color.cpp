#include "externals.h"
#include "color.h"

Float3 hsvToRgb(const Float3& hsv)
{
	const float h = hsv[0];
	const float s = hsv[1];
	const float v = hsv[2];

	if (s == 0)
		return {0,0,0};

	const auto i = static_cast<int>(h * 6) % 6;
	const float f = h - i;

	const float p = v * (1.0f - s);
	const float q = v * (1.0f - s * f);
	const float t = v * (1.0f - s * (1.0f - f));

	switch (i)
	{
	case 0: return {v,t,p};
	case 1: return {q,v,p};
	case 2: return {p,v,t};
	case 3: return {p,q,v};
	case 4: return {t,p,v};
	default: return {v,p,q};
	}
}
