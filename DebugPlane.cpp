#include "DebugPlane.hpp"

#include <random>

#include "Debug.hpp"

using namespace MeshStatsDefinition;

DebugPlaneDefinition::DebugPlane::DebugPlane()
{

}

DebugPlaneDefinition::DebugPlane::~DebugPlane()
{
}

void DebugPlaneDefinition::DebugPlane::addTri(vector<int> indices)
{
	IndexedTriangle tri;

	tri[0] = indices[0];
	tri[1] = indices[1];
	tri[2] = indices[2];

	triangles.push_back(tri);
}

DebugPlaneDefinition::DebugPlane::DebugPlane(v3 center, v3 normal, float width, float height, v4 color)
{
	//params
	normal = glm::normalize(normal);
	v3 tangent = glm::cross(normal, v3(-normal.z, normal.x, normal.y));
	v3 biTangent = glm::cross(normal, tangent);

	v3 topRight = center + (width / 2) * tangent + (height / 2) * biTangent;
	v3 bottomRight = center + (width / 2) * tangent - (height / 2) * biTangent;
	v3 topLeft = center - (width / 2) * tangent + (height / 2) * biTangent;
	v3 bottomLeft = center - (width / 2) * tangent - (height / 2) * biTangent;

	vertices.push_back(topRight);
	vertices.push_back(bottomRight);
	vertices.push_back(topLeft);
	vertices.push_back(bottomLeft);

	addTri({ 3, 1, 0 });
	addTri({ 3, 0, 1 });
	addTri({ 3, 2, 0 });
	addTri({ 3, 0, 2 });

	colorDataUniformly(color);

	bind();
}