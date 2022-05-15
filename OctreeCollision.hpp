#ifndef OctreeCollision_HPP
#define OctreeCollision_HPP

#include "MeshStats.hpp"

namespace OctreeCollisionDefinition
{

	using namespace MeshStatsDefinition;

	struct OctreeCollision
	{
		OctreeCollision();
		~OctreeCollision();
		TriangleID triangleID; // triangle id the collision occurs
		float distance; // distance from start to collision point.
		v3 position; // of collision
	};
}

#endif // !OctreeCollision_HPP

