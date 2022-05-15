#ifndef MeshStats_HPP
#define MeshStats_HPP

#include "GraphicsData.hpp"


namespace MeshStatsDefinition
{
	using namespace GraphicsDataDefinition;

	/*
	*	A collection of Mesh Stats - data collection purposes
	*   Inherited by Mesh
	*/
	class MeshStats : public GraphicsData
	{
		public:
			MeshStats();
			~MeshStats();

			void collectStats(); 

			v3 limMax = v3(0);
			v3 limMin = v3(0);
			v3 center = v3(0);

	};
}

#endif 
