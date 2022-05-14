#include "MortonCode.hpp"

int MortonCodeDefinition::mortonCodeHash(rv3 point, rv3 center)
{
	// this function is performing a safety test on point.members that are "0" on an axis. 
	// Due to the nature of floating points, -0.0f is possible and less than 0.0f, so this function takes this into account and auto converts -0.0f into 0.0f if it exists so there are no errors in the MortonCode produced.
    return (MortonCodeConvert_Safe(point.x, center.x) << 2) | (MortonCodeConvert_Safe(point.y, center.y) << 1) | (MortonCodeConvert_Safe(point.z, center.z));
}
