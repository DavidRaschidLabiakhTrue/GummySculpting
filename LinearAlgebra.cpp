#include "LinearAlgebra.hpp"
using namespace LinearAlgebra;

glm::vec3 midpointFromV3(glm::vec3& p1, glm::vec3& p2)
{
	return (p1 + p2) * 0.5f;
}
