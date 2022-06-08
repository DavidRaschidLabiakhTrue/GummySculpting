#include "LinearAlgebra.hpp"
using namespace LinearAlgebra;

glm::vec3 LinearAlgebra::midpointFromV3(glm::vec3& p1, glm::vec3& p2)
{
	return (p1 + p2) * 0.5f;
}

glm::vec3 LinearAlgebra::getRayPlaneIntersect(glm::vec3 planeP, glm::vec3 planeN, glm::vec3 rayP, glm::vec3 rayD)
{
    float d = glm::dot(planeP, -planeN);
    float t = -(d + rayP.z * planeN.z + rayP.y * planeN.y + rayP.x * planeN.x) / (rayD.z * planeN.z + rayD.y * planeN.y + rayD.x * planeN.x);
    return rayP + t * rayD;
}

glm::vec4 LinearAlgebra::planePointNormalToGeneralForm(glm::vec3 point, glm::vec3 normal)
{
    float d = normal.x * point.x + normal.x * point.y + normal.x * point.z;
    return glm::vec4(normal.x, normal.y, normal.z, d);
}

float LinearAlgebra::distanceFromPointToPlane(glm::vec3 pointP, glm::vec3 planeP, glm::vec3 planeN)
{
    glm::vec4 plane = planePointNormalToGeneralForm(planeP, planeN);
    float d = fabs(plane[0] * pointP.x + plane[1] * pointP.y + plane[2] * pointP.z + plane[3]);
    float e = sqrt(plane[0] * plane[0] + plane[1] * plane[1] + plane[2] * plane[2]);
    return d / e;
}

float LinearAlgebra::distanceFromPointToPlane(glm::vec3 pointP, glm::vec4 plane)
{
    float d = fabs(plane[0] * pointP.x + plane[1] * pointP.y + plane[2] * pointP.z + plane[3]);
    float e = sqrt(plane[0] * plane[0] + plane[1] * plane[1] + plane[2] * plane[2]);
    return d / e;
}

float LinearAlgebra::eulerFromMatrix_X(glm::mat4 matrix)
{
    return atan2(matrix[2][1], matrix[2][2]);
}

float LinearAlgebra::eulerFromMatrix_Y(glm::mat4 matrix)
{
    return atan2(matrix[2][0], sqrt(pow(matrix[2][1], 2) + pow(matrix[2][2], 2)));
}

float LinearAlgebra::eulerFromMatrix_Z(glm::mat4 matrix)
{
    return atan2(matrix[1][0], matrix[0][0]);
}