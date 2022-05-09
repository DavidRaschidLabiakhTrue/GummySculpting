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

	class RayCast : protected GraphicsData, public IndiceList
	{
		public:
			Empty_Construct RayCast();
			RayCast(bool trueConstruct);
			~RayCast();

			void cast(); // fire out a ray cast if clicking and collect ray data


			void drawRay();

			

			

			void setOrigin();

			void setEnd(float length = 200);

			RV3D origin();
			RV3D end();

			bool shouldDrawRay = true;
			v3 direction = v3(0,0,0);
			void screenToWorld();
			void bindRay();
			void refreshRay();


	};

}

#endif
