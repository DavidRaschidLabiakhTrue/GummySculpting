#ifndef DebugLine_HPP
#define DebugLine_HPP


#include "RayCasting.hpp"

namespace DebugLineDefinition
{
	using namespace RayCastDefinition;

	class DebugLine : protected RayCast
	{
		public:
			Empty_Construct DebugLine();
			DebugLine(bool trueConstruct);
			~DebugLine();

			void setOrigin(v3 origin);
			void setEnd(v3 end);
			void drawLine();
			void setColor(v4 color);
	};
}

#endif