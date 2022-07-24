#ifndef RayCasting_HPP
#define RayCasting_HPP


#include "GraphicsData.hpp"
#include "IndiceList.hpp"
#include "Window_API.hpp"





namespace RayCastDefinition
{
	using namespace GraphicsDataDefinition;
	using namespace IndiceListDefinition;
	using namespace Window_API;

	// implementation of a ray casting mechanic
	class RayCast : public GraphicsData, public IndiceList
	{
		public:
			Empty_Construct RayCast();
			RayCast(bool trueConstruct);
			~RayCast();

			bool cast(); // fire out a ray cast if clicking and collect ray data


			void drawRay();

			

			

			void setOrigin();

			void setEnd(float length = 200);

			RV3D origin();
			RV3D end();

			bool shouldDrawRay = false;
			v3 direction = v3(0,0,0);
			v3 start = v3(0, 0, 0);
			void screenToWorld();
			void bindRay();
			void refreshRay();


	};

}

#endif
