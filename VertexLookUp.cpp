#include "VertexLookUp.hpp"

using namespace VertexLookUpDefinition;

VertexLookUpDefinition::VertexLookUp::VertexLookUp()
{

}

VertexLookUpDefinition::VertexLookUp::~VertexLookUp()
{
}

KeyData VertexLookUpDefinition::VertexLookUp::closest(rv3 pointToTest, RIndexTriangle tri)
{
	const float dist1 = distance(vertices[tri[0]].position, pointToTest);
	const float dist2 = distance(vertices[tri[1]].position, pointToTest);
	const float dist3 = distance(vertices[tri[2]].position, pointToTest);

	if (dist1 <= dist2 and dist1 <= dist3)
	{
		return tri[0];
	}
	eif(dist2 <= dist1 and dist2 <= dist3)
	{
		return tri[1];
	}
	return tri[2];
}

RV3D VertexLookUpDefinition::VertexLookUp::lookUpV3D(KeyData key)
{
	return vertices[key];
}

RIndexTriangle VertexLookUpDefinition::VertexLookUp::lookUpTriangle(KeyData key)
{
	return triangles[key];
}

KeyData VertexLookUpDefinition::VertexLookUp::findClosest(rv3 testpoint, KeyData p0, KeyData p1, KeyData p2)
{
	KeyData closest = ImpossibleKey;
	return closest;
}
