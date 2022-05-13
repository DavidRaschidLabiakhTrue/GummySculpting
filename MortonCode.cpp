#include "MortonCode.hpp"

int MortonCodeDefinition::mortonCodeHash(rv3 point, rv3 center)
{
    return (MortonCodeConvert_Safe(point.x, center.x) << 2) | (MortonCodeConvert_Safe(point.y, center.y) << 1) | (MortonCodeConvert_Safe(point.z, center.z));
}
