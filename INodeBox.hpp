#ifndef INodeBox_HPP
#define INodeBox_HPP

#include "MeshStats.hpp"
#include "INodeMortonCode.hpp"

namespace INodeBoxDefinition
{
	using namespace MeshStatsDefinition;
	using namespace INodeMortonCodeDefinition;
	// box structure
	struct INodeBox
	{
		public:
			INodeBox();
			~INodeBox();

			void loadBox(rv3 newCenter, float newHalfSize);

			v3 boxTopFrontLeft();
			v3 boxTopFrontRight();

			v3 boxTopBackLeft();
			v3 boxTopBackRight();

			v3 boxBottomFrontLeft();
			v3 boxBottomFrontRight();

			v3 boxBottomBackLeft();
			v3 boxBottomBackRight();

			float halfOfBoxHalfSize();
			

			v3 boxCenter = v3(0,0,0);
			float boxHalfSize = 1.0f;

			
	};
}

#endif
