#include "Color.hpp"

Usage ColorDefinition;

v4 convert_255colorScale_to_0_1colorscale(float r, float g, float b, float a)
{
	return v4(ConvertColorScale(r,g,b,a));
}
