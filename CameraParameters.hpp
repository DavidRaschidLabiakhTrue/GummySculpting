#ifndef CameraParameters_HPP
#define CameraParameters_HPP

#include "Window_API.hpp"
#include "MathDefinitions.hpp"

Usage Window_API;

namespace CameraParametersDefinition
{
	struct CameraParameters
	{
		public:
			Construct CameraParameters();
			Deconstruct ~CameraParameters();
		protected:
			float farPlane;
			float nearPlane;
			float fov;
			float speed;
			float sensitivity;
	};
}

#endif
