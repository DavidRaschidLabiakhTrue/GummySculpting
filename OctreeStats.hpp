#ifndef OctreeStats_HPP
#define OctreeStats_HPP

#include "MeshStats.hpp"
#include "TriangleOctantKeyPairList.hpp"

namespace OctreeStatsDefinition
{
	using namespace MeshStatsDefinition;
	using namespace TriangleOctantKeyPairListDefinition;

	class OctreeStats : public TriangleOctantKeyPairList
	{
		public:
			OctreeStats();
			~OctreeStats();

			int octantTriangleLimit = 1000;
			int octreeDepthLimit = 10;
			int octreeDepth = 0;
			float octreeBuffer = 1.5;
			double octreeLooseness = 1.2;
			int octreeCurrentDepth = 0;
			OctantIndex root = 0;
	};
}

#endif
