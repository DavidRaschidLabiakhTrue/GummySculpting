#ifndef MeshStats_HPP
#define MeshStats_HPP

#include "GraphicsData.hpp"


namespace MeshStatsDefinition
{
	Usage GraphicsDataDefinition;

	/*
	*	A collection of Mesh Stats - data collection purposes
	*   Inherited by Mesh
	*/
	class MeshStats : public GraphicsData
	{
		public:
			Construct MeshStats();
			Deconstruct ~MeshStats();

			void collectStats(); // unimplemented, need to add ryan and jiahao's code here.

			v3 limMax = v3(0);
			v3 limMin = v3(0);
			v3 center = v3(0);

	};
}

#endif 
