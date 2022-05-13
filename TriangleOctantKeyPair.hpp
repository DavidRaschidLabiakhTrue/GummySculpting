#ifndef TriangleOctantKeyPair_HPP
#define TriangleOctantKeyPair_HPP

#include "MeshStats.hpp"

namespace TriangleOctantKeyPairDefinition
{
	using namespace MeshStatsDefinition;

	typedef int OctantIndex;

	struct TriangleOctantKeyPair
	{
		public:
			TriangleOctantKeyPair();
			TriangleOctantKeyPair(IndexedTrianglePosition triPosition, OctantIndex octIndex);

			~TriangleOctantKeyPair();

			IndexedTrianglePosition triangleIndex;
			OctantIndex octantIndex;
	};
}

#endif // !TriangleOctantKeyPair_HPP
