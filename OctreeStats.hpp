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

			int limit = 1000;
			int depthLimit = 10;
			int depth = 0;
			double looseness = 0.2;
			int currentDepth = 0;


	};
}

#endif
