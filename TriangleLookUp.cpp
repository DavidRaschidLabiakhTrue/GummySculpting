#include "TriangleLookUp.hpp"

using namespace EdgeListDefinition;
using namespace LinearAlgebra;

using namespace TriangleLookUpDefinition;

TriangleLookUpDefinition::TriangleLookUp::TriangleLookUp()
{
}

TriangleLookUpDefinition::TriangleLookUp::~TriangleLookUp()
{
}

v3 TriangleLookUpDefinition::TriangleLookUp::getTriangleNormal(IndexedTriangleID key)
{
	const auto v0 = vertices[triangles[key][0]].position;
	const auto v1 = vertices[triangles[key][1]].position;
	const auto v2 = vertices[triangles[key][2]].position;

	const auto res = cross(v1 - v0, v2 - v1);
	const float leng = length(res);
	if (leng > 0.0f)
	{
		return res / leng; // basically normalizes the resulant vector
	}
	return v3(0); // improper normal
}

v3 TriangleLookUpDefinition::TriangleLookUp::getTriangleCentroid(IndexedTriangleID key)
{
	return (vertices[triangles[key][0]].position + vertices[triangles[key][1]].position + vertices[triangles[key][0]].position) / 3.0f; // average
}
