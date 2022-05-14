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

			int octreeLimit = 1000;
			int octreeDepthLimit = 10;
			int octreeDepth = 0;
			double octreeLooseness = 0.2;
			int octreeCurrentDepth = 0;


	};
}

#endif
