#include "externals.h"
#include "sceneTypes.h"

using namespace coveo::linq;

namespace Semantic
{
	SemanticKinds generateKinds()
	{
		SemanticKinds kinds;

		for (auto i = 0; i < COUNT; ++i)
		{
			kinds[i] = static_cast<Kind>(i);
		}

		return move(kinds);
	}

	const SemanticKinds& kinds()
	{
		static SemanticKinds kinds{ generateKinds() };
		return kinds;
	}

	const SemanticKinds& blendShapeKinds()
	{
		static SemanticKinds kinds{ POSITION, NORMAL, TANGENT };
		return kinds;
	}
}
