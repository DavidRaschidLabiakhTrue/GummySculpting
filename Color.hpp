#ifndef Color_HPP
#define Color_HPP

#include "MathDefinitions.hpp"

// UNUSED

namespace ColorDefinition
{
	Usage MathTypeDefinitions::CoordinateDefine;

	#define ConvertColorScale(r,g,b,a) (r) / 255.0f, (g) / 255.0f, (b) / 255.0f, (a) / 255.0f  

	extern v4 convert_255colorScale_to_0_1colorscale(float r, float g, float b, float a = 255.0f);

}


#endif //Color_HPP
