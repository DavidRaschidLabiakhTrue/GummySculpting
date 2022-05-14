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
		TriangleID triangle; // triangle id the collision occurs
		float distance; // distance from start to collision point.
		v3 pos; // of collision
	};
}

#endif // !OctreeCollision_HPP

