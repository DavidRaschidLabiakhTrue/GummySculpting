#ifndef OctreeStats_HPP
#define OctreeStats_HPP

#include "MeshStats.hpp"

namespace OctreeStatsDefinition
{
	using namespace MeshStatsDefinition;

	class OctreeStats : public MeshStats
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
