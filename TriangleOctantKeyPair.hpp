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
			TriangleOctantKeyPair(IndexedTriangleID triPosition, OctantIndex octIndex);

			~TriangleOctantKeyPair();

			IndexedTriangleID triangleIndex;
			OctantIndex octantIndex;
	};
}

#endif // !TriangleOctantKeyPair_HPP
