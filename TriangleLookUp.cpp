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
	return triangleNormal(vertices[triangles[key][0]].position, vertices[triangles[key][1]].position, vertices[triangles[key][2]].position);
}

v3 TriangleLookUpDefinition::TriangleLookUp::getTriangleCentroid(IndexedTriangleID key)
{
	return (vertices[triangles[key][0]].position + vertices[triangles[key][1]].position + vertices[triangles[key][0]].position) / 3.0f; // average
}
