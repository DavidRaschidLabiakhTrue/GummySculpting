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
	pos = startPos = v3(0, 0, 2.0f);
	focalPoint = v3(0);

	view = m4(1.0);
	projection = m4(1.0);
	cameraMatrix = m4(1.0f);

	farPlane = 100.0f;
	nearPlane = 0.1f;
	sensitivity = 100.0f;
	speed = 0.09f;
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
		v3 changeInPos = v3(0);
		if (CheckKeyHeld(GLFW_KEY_W))
		{
			changeInPos += speed * orientation;

		}
		else if (CheckKeyHeld(GLFW_KEY_S))
		{
			changeInPos += speed * -orientation;

		}

		if (CheckKeyHeld(GLFW_KEY_A))
		{
			changeInPos += speed * -glm::normalize(glm::cross(orientation, up));

		}
		else if (CheckKeyHeld(GLFW_KEY_D))
		{
			changeInPos += speed * glm::normalize(glm::cross(orientation, up));

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

		if (CheckKeyHeld(GLFW_KEY_R))
		{
			//resetViewAndPos(); // unimplemented
		}
		if (CheckKeyHeld(GLFW_KEY_SPACE))
		{
			changeInPos += speed * up;
		}
		else if (CheckKeyHeld(GLFW_KEY_X))
		{
			changeInPos += speed * -up;
		}

		focalPoint += changeInPos;
		pos += changeInPos;

		// speed
		if (CheckKeyHeld(GLFW_KEY_LEFT_SHIFT))
		{
			speed = 0.1f;
		}
		else
		{
			speed = 0.06f;
		}
	}
}

void CameraDefinition::Camera::checkMouseInput()
{
	//consume scroll input to zoom camera in and out
	double scroll_val = WindowGlobal::ActiveWindow->scroll_val;
	pos *= 1 - 0.1 * (scroll_val > 0) + 0.1 * (scroll_val < 0);
	WindowGlobal::ActiveWindow->scroll_val = 0;

	switch (cameraState)
	{
	case FREEFOCUS:
		if (CheckMouseHeld(GLFW_MOUSE_BUTTON_MIDDLE))
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
		break;
	case ORBIT:
		if (CheckMouseHeld(GLFW_MOUSE_BUTTON_MIDDLE))
		{
			const auto winDim = WindowDimensions(); // get the window dimensions.



			//check distance to center
			float distance = glm::distance(pos, focalPoint);

			// Prevent Camera Jumping on load.
			if (firstClick)
			{
				setMousePosition((double)winDim.width / 2, (double)winDim.height / 2);
				firstClick = false;
			}
			const auto ms = MouseCoordinates(); // get the mouse coordinates.
			float rotX = sensitivity * (float)(ms.msy - ((winDim.height) / 2)) / winDim.height;
			float rotY = sensitivity * (float)(ms.msx - ((winDim.width) / 2)) / winDim.height;

			v3 oldOrientation = orientation;

			// Calculates upcoming vertical change in the Orientation
			v3 newOrientation = rotate(orientation, radians(-rotX), normalize(cross(orientation, up)));

			// Decides whether or not the next vertical Orientation is legal or not
			if (abs(angle(newOrientation, up) - radians(90.0f)) <= radians(85.0f))
			{
				orientation = newOrientation;
			}


			// Rotates the Orientation left and right
			orientation = rotate(orientation, radians(-rotY), up);


			v3 offset = (orientation - oldOrientation) * distance;

			pos -= offset;

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
		break;
	default:
		break;
	}
	
}
