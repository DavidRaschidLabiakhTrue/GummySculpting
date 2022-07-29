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

float TriangleLookUpDefinition::TriangleLookUp::getTriangleArea(IndexedTriangleID key)
{
    // if (glm::any(glm::isnan(vertices[triangles[key][0]].position)) ||
    //     glm::any(glm::isnan(vertices[triangles[key][1]].position)) ||
    //     glm::any(glm::isnan(vertices[triangles[key][2]].position)))
    // {
    //     return 0.0f;
    // }

    float a = glm::distance(vertices[triangles[key][0]].position, vertices[triangles[key][1]].position);
    float b = glm::distance(vertices[triangles[key][1]].position, vertices[triangles[key][2]].position);
    float c = glm::distance(vertices[triangles[key][2]].position, vertices[triangles[key][0]].position);
    float s = (a + b + c) * 0.5f;
    return glm::sqrt(s * (s - a) * (s - b) * (s - c));
}
