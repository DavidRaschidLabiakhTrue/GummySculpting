#include "Camera.hpp"
#include "KeyInput.hpp"
#include "MathDefinitions.hpp"

namespace CameraDefinition
{
	CameraPTR GlobalCamera = UnassignedPTR;
}
Usage Window_API::Window_API_Functions;
Usage Window_API::Window_API_Structures;

Usage Window_API;
Usage CameraDefinition;
Usage KeyInputDefinition;

Usage MathTypeDefinitions;



Camera::Camera()
{
	orientation = v3(0.0f, 0.0f, -1.0f);
	up = v3(0.0f, 1.0f, 0.0f);
	pos = v3(0, 0, 2.0f);



	view = m4(1.0);
	projection = m4(1.0);
	cameraMatrix = m4(1.0f);

	farPlane = 100.0f;
	nearPlane = 0.1f;
	sensitivity = 100.0f;
	speed = 0.01f;
	fov = 45.0f; // degrees
}

Camera::~Camera()
{
}

void CameraDefinition::Camera::checkInput()
{
	checkKeyInput();
	checkMouseInput();
}

void CameraDefinition::Camera::updateMatrix()
{
	view = m4(1.0f); // these are Ones Matrices
	projection = m4(1.0f); // these are Ones Matrice

	// Makes camera look in the right direction from the right position
	view = lookAt(pos, pos + orientation, up);
	// Adds perspective to the scene
	const auto winDim = WindowDimensions();
	projection = perspective(radians(fov), (float)winDim.width / (float)winDim.height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void CameraDefinition::Camera::checkKeyInput()
{
	auto& io = ImGui::GetIO();
	
	// Handles key inputs
	if(!io.WantCaptureMouse)
	{
		if (CheckKeyPressed(GLFW_KEY_W))
		{
			pos += speed * orientation;

		}

		if (CheckKeyPressed(GLFW_KEY_A))
		{
			pos += speed * -glm::normalize(glm::cross(orientation, up));

		}
		if (CheckKeyPressed(GLFW_KEY_S))
		{
			pos += speed * -orientation;

		}
		/*
		* // Problematic system
		// this case consumes mouse scroll wheel input and moves the view forward or backwards. It uses a distance multiplier to also operate.
		if (WindowGlobal::ActiveWindow->scroll_state != 0)
		{
			pos += (float)(WindowGlobal::ActiveWindow->scroll_state * 10 * speed) * orientation;
			WindowGlobal::ActiveWindow->scroll_state = 0;
		}
		*/
		if (CheckKeyPressed(GLFW_KEY_D))
		{
			pos += speed * glm::normalize(glm::cross(orientation, up));

		}
		if (CheckKeyPressed(GLFW_KEY_R))
		{
			//resetViewAndPos(); // unimplemented
		}
		if (CheckKeyPressed(GLFW_KEY_SPACE))
		{
			pos += speed * up;
		}
		if (CheckKeyPressed(GLFW_KEY_LEFT_CONTROL))
		{
			pos += speed * -up;
		}
		// speed
		if (CheckKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			speed = 0.04f;
		}
		else
		{
			speed = 0.01f;
		}
	}
}

void CameraDefinition::Camera::checkMouseInput()
{
	if (CheckMousePressed(GLFW_MOUSE_BUTTON_MIDDLE))
	{
		const auto winDim = WindowDimensions(); // get the window dimensions.

		// Prevent Camera Jumping on load.
		if (firstClick)
		{
			setMousePosition((double)winDim.width / 2, (double)winDim.height / 2);
			firstClick = false;
		}
		const auto ms = MouseCoordinates(); // get the mouse coordinates.
		float rotX = sensitivity * (float)(ms.msy - ((winDim.height) / 2)) / winDim.height;
		float rotY = sensitivity * (float)(ms.msx - ((winDim.width) / 2)) / winDim.height;
		// Calculates upcoming vertical change in the Orientation
		v3 newOrientation = rotate(orientation, radians(-rotX), normalize(cross(orientation, up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(angle(newOrientation, up) - radians(90.0f)) <= radians(85.0f))
		{
			orientation = newOrientation;
		}


		// Rotates the Orientation left and right
		orientation = rotate(orientation, radians(-rotY), up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		setMousePosition((double)winDim.width / 2, (double)winDim.height / 2); // this is the center of the screen.
	}
	eif(CheckMouseReleased(GLFW_MOUSE_BUTTON_MIDDLE))
	{
		// Unhides cursor since camera is not looking around anymore
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
		return;
	}
}
