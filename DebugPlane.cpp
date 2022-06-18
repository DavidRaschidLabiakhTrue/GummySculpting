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



DebugPlaneDefinition::DebugPlane::DebugPlane(v3 center, v3 normal, float width, float height, v4 color)
{
	vertices.resize(4);

	calcVertices(center, normal, width, height);

	addTri({ 3, 1, 0 });
	addTri({ 3, 0, 1 });
	addTri({ 3, 2, 0 });
	addTri({ 3, 0, 2 });

	colorDataUniformly(color);

	bind();
}

void DebugPlaneDefinition::DebugPlane::addTri(vector<int> indices)
{
	IndexedTriangle tri;

	tri[0] = indices[0];
	tri[1] = indices[1];
	tri[2] = indices[2];

	triangles.push_back(tri);
}

void DebugPlaneDefinition::DebugPlane::calcVertices(v3 center, v3 normal, float width, float height)
{
	normal = glm::normalize(normal);
	v3 tangent = glm::cross(normal, v3(-normal.z, normal.x, normal.y));
	v3 biTangent = glm::cross(normal, tangent);

	vertices[0].position = center + (width / 2) * tangent + (height / 2) * biTangent;
	vertices[1].position = center + (width / 2) * tangent - (height / 2) * biTangent;
	vertices[2].position = center - (width / 2) * tangent + (height / 2) * biTangent;
	vertices[3].position = center - (width / 2) * tangent - (height / 2) * biTangent;
}