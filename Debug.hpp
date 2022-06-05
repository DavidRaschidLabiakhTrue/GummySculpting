#ifndef Debug_HPP
#define Debug_HPP

#include <string>
#include "DebugLine.hpp"
#include "MathDefinitions.hpp"

namespace Debug
{
	using namespace MathTypeDefinitions::CoordinateDefine;

	namespace Drawing
	{
		void drawLine(v3 origin, v3 end, v4 color = v4(0.0f, 0.65f, 1.0f, 1.0f));
		void renderLines();
	}
}

#endif