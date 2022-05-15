#include "INodeMortonCode.hpp"
using namespace INodeMortonCodeDefinition;

INodeMortonCodePosition inodeMortonCodePosition(rv3 testPoint, rv3 center)
{
	// This is a switch to allow for readable debugging.
	switch ((testPoint.x >= center.x) << 2 | (testPoint.y >= center.y) << 1 | (testPoint.z >= center.z))
	{
		case TopFrontLeft:
			return INodeMortonCodePosition::TopFrontLeft;

		case TopFrontRight:
			return INodeMortonCodePosition::TopFrontRight;

		case TopBackRight:
			return INodeMortonCodePosition::TopBackRight;

		case TopBackLeft:
			return INodeMortonCodePosition::TopBackLeft;

		case BottomFrontLeft:
			return INodeMortonCodePosition::BottomFrontLeft;

		case BottomFrontRight:
			return INodeMortonCodePosition::BottomFrontRight;

		case BottomBackRight:
			return INodeMortonCodePosition::BottomBackRight;

		case BottomBackLeft:
			return INodeMortonCodePosition::BottomBackLeft;

		default:
			say "MORTON CODE FAILURE" done;
			return INodeMortonCodePosition::TopFrontLeft;


	}
}
