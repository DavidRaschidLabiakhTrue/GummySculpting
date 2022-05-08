#include "CameraParameters.hpp"

Usage CameraParametersDefinition;

CameraParameters::CameraParameters()
{
	farPlane = 100.0f;
	nearPlane = 0.1f;
	sensitivity = 100.0f;
	speed = 0.01f;
	fov = 45.0f; // degrees
}

CameraParameters::~CameraParameters()
{
}
