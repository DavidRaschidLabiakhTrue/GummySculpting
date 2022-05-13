#ifndef LinearAlgebra_HPP
#define LinearAlgebra_HPP


#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/epsilon.hpp>
#include "glm/gtx/norm.hpp"

#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtx/intersect.hpp"

#include "glm/fwd.hpp"

// container wrapper for numerous glm functions. Also heavily reduces compile time by including only what's needed by header
namespace LinearAlgebra
{
	using glm::all;
	using glm::lessThanEqual;
	using glm::greaterThanEqual;
	using glm::max;
	using glm::min;
	using glm::to_string;
	using glm::lookAt;
	using glm::value_ptr;
	using glm::cross;
	using glm::dot;
	using glm::length;
	using glm::distance;
	using glm::unProject;
	using glm::normalize;

	using glm::perspective;
	using glm::inverse;
	using glm::rotate;
	using glm::sin;
	using glm::cos;
	using glm::tan;
	using glm::atan;
	using glm::atanh;
	using glm::acos;
	using glm::acosh;
	using glm::asin;
	using glm::asinh;

	using glm::pi;
	using glm::e;

	using glm::radians;
	using glm::degrees;

	using glm::angle;

	using glm::intersectLineTriangle;
	using glm::intersectRayTriangle;
}

#endif 
