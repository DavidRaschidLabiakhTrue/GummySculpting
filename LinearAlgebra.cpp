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