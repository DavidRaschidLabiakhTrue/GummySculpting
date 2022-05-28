#ifndef OctreeCollision_HPP
#define OctreeCollision_HPP

#include "MeshStats.hpp"
#include "Octant.hpp"
#include "TriangleOctantKeyPairList.hpp"

namespace OctreeCollisionDefinition
{

	using namespace MeshStatsDefinition;
	using namespace TriangleOctantKeyPairDefinition;

	#define NoCollisionDistance numeric_limits<float>::max()

	struct OctreeCollision
	{
		TriangleID triangleID; // triangle id the collision occurs
		float distance = NoCollisionDistance; // distance from start to collision point.
		v3 position; // of collision
		bool isCollision = false; // is there a collision
		OctantIndex octantID;
	};
}

#endif // !OctreeCollision_HPP

