#include "TopologyComputation.hpp"

using namespace TopologyComputationDefinition;

bool TopologyComputationDefinition::intersectionMoller(rv3 origin, rv3 direction, rv3 p0, rv3 p1, rv3 p2, rv3 intersectionPoint)
{
	const auto epsilonVal = 0.0000001f;
	const v3 edge1 = p1 - p0;
	const v3 edge2 = p2 - p0;

	const v3 h = cross(direction, edge2);
	// im going off the documentation.
	const float a = dot(edge1, h);

	if (a > -epsilonVal and a < epsilonVal)
	{
		return false;
	}
	const float f = 1.0f / a;
	const v3 s = origin - p0;
	const float u = f * dot(s, h);

	if (u < 0.0f or u > 1.0f)
	{
		return false;
	}
	const v3 q = cross(s, edge1);
	const float v = f * dot(direction, q);
	if (v < 0.0f or (u + v) > 1.0f)
	{
		return false;
	}
	const float t = f * dot(edge2, q);
	if (t > epsilonVal)
	{
		intersectionPoint = origin + direction * t;
		return true;
	}

    return false;
}

bool TopologyComputationDefinition::swapRayAxisAndOrigin(rv3 originalDir, rv3 originalOrigin, rv3 newDir, rv3 newOrigin)
{
	if (originalOrigin.x == 0.0f and originalDir.x == 0.0f)
	{
		return false; // we are starting at the center and we are pointing down the middle. Symmetry is not possible from the center
	}

	// the direction is normalized already, 

	// assuming the ray does not get centered

	newDir = v3(-1.0f * originalDir.x, originalDir.y, originalDir.z);
	newOrigin = v3(-1.0f * originalOrigin.x, originalOrigin.y, originalOrigin.z); // I need to draw the ray

	say "old dir" spc to_string(originalDir); say "new dir" spc to_string(newDir) done;

	say "old origin" spc to_string(originalOrigin); say "new origin" spc to_string(newOrigin) done;



	return true;
}


