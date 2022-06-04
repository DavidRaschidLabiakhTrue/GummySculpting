#ifndef MathDefinitions_HPP
#define MathDefinitions_HPP

#include "LinearAlgebra.hpp"

#include "Macro.hpp"
// shortens up linear algebra type names.
namespace MathTypeDefinitions
{
	Usage Macros;
	Usage glm;

	// defines coordinates in space
	namespace CoordinateDefine
	{
		typedef glm::vec2 v2;
		typedef glm::vec3 v3;
		typedef glm::vec4 v4; // r g b a

		typedef v3& rv3; // vector 3 reference
		typedef v4& rv4; // vector 4 reference - r g b a
		
	}
	// defines matrices of dim 2 to 4
	namespace MatrixDefine
	{
		typedef glm::mat2 m2; // matrix dim 2x2
		typedef glm::mat3 m3; // matrix dim 3x3
		typedef glm::mat4 m4; // matrix dim 4x4 - most common

		typedef m4& rm4;

	}

}
namespace MathTypeDefinitions::CoordinateDefine::Basis
{
	const v3 X = v3(1, 0, 0);
	const v3 Y = v3(0, 1, 0);
	const v3 Z = v3(0, 0, 1);

	const v3 XY = v3(1, 1, 0);
	const v3 XZ = v3(1, 0, 1);
	const v3 YZ = v3(0, 1, 1);
}

#endif

