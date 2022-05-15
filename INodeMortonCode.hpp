#ifndef INodeMortonCode_HPP
#define INodeMortonCode_HPP

#include "MeshStats.hpp"

namespace INodeMortonCodeDefinition
{
	using namespace MeshStatsDefinition;

	enum INodeMortonCodePosition
	{
		TopFrontLeft = 0,
		TopFrontRight = 2,

		TopBackRight = 3,
		TopBackLeft = 1,

		BottomFrontLeft = 4,
		BottomFrontRight = 6,

		BottomBackRight = 7,
		BottomBackLeft = 5
	};

	INodeMortonCodePosition inodeMortonCodePosition(rv3 testPoint, rv3 center);

}

#endif // !INodeMortonCode_HPP

