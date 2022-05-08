#ifndef MeshStats_HPP
#define MeshStats_HPP

#include "GraphicsData.hpp"

namespace MeshStatsDefinition
{
	Usage GraphicsDataDefinition;

	/*
	*	A collection of Mesh Stats
	*   Inherited by Mesh
	*/
	class MeshStats : public GraphicsData
	{
		public:
			Construct MeshStats();
			Deconstruct ~MeshStats();

			void collectStats();

			v3 limMax = v3(0);
			v3 limMin = v3(0);
			v3 center = v3(0);
			float halfSize = 0; // only a default computed value.
	};
}

#endif 
