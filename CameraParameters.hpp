#ifndef CameraParameters_HPP
#define CameraParameters_HPP

#include "Window_API.hpp"
#include "MathDefinitions.hpp"

Usage Window_API;

namespace CameraParametersDefinition
{
	// container for numerous camera parameters. Allows for fine tuning to occur.
	struct CameraParameters
	{
		public:
			Construct CameraParameters();
			Deconstruct ~CameraParameters();
			float farPlane;
			float nearPlane;
			float fov;
			float speed;
			float sensitivity;
	};
}

#endif
