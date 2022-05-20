#ifndef OctreeCollision_HPP
#define OctreeCollision_HPP

#include "MeshStats.hpp"

namespace OctreeCollisionDefinition
{

	using namespace MeshStatsDefinition;

	#define NoCollisionDistance std::numeric_limits<float>::max()

	struct OctreeCollision
	{
		TriangleID triangleID; // triangle id the collision occurs
		float distance; // distance from start to collision point.
		v3 position; // of collision
		bool isCollision = false; // is there a collision
	};
}

#endif // !OctreeCollision_HPP

