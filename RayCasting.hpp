#ifndef RayCasting_HPP
#define RayCasting_HPP


#include "GraphicsData.hpp"
#include "IndiceList.hpp"

namespace RayCastDefinition
{
	using namespace GraphicsDataDefinition;
	using namespace IndiceListDefinition;

	class RayCast : protected GraphicsData, public IndiceList
	{
		public:
			RayCast();
			~RayCast();

			void bindRay();
			void refreshRay();

			void redirectRay();

			void drawRay();

			bool shouldDrawRay = true;

			void screenToWorld();

			void setOrigin();

			void setEnd(float length = 200);

			RV3D origin();
			RV3D end();

			v3 direction = v3(0,0,0);


	};

}

#endif
