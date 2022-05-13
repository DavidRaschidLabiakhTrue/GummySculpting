#ifndef MortonCode_HPP
#define MortonCode_HPP

#include "MathDefinitions.hpp"
#include <cmath> // std::signbit

namespace MortonCodeDefinition
{
	using namespace MathTypeDefinitions::CoordinateDefine;
	
	// I am aware of the line size.
	#define MortonCodeConvert_Safe(MortonCodeVertexPosition, MortonCodeCenterPosition) (((((MortonCodeVertexPosition) == 0.0f) && std::signbit((MortonCodeVertexPosition))) ? 0.0f : (MortonCodeVertexPosition)) >= (MortonCodeCenterPosition))

	inline int mortonCodeHash(rv3 point, rv3 center); // returns the morton code position with respect to octant
}

#endif // !MortonCode_HPP

