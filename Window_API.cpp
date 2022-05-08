#include "Window_API.hpp"

namespace Window_API
{
	WindowAPIData WinAPI;
}

Usage Window_API;
Usage Window_Class;

Window_API_Structures::MouseCoordinates::MouseCoordinates()
{
	glfwGetCursorPos(winGB::ActiveWindowPTR, &msx, &msy);
}

Window_API_Structures::MouseCoordinates::~MouseCoordinates()
{
}

Window_API_Structures::WindowDimensions::WindowDimensions()
{
	glfwGetWindowSize(winGB::ActiveWindowPTR, &width, &height);
}
Window_API_Structures::WindowDimensions::~WindowDimensions()
{
}

Window_API_Structures::ScreenData::ScreenData()
{
	glfwGetCursorPos(winGB::ActiveWindowPTR, &msx, &msy);
	glfwGetWindowSize(winGB::ActiveWindowPTR, &width, &height);

	translationVector = v4(0, 0, width, height);
}

Window_API_Structures::ScreenData::~ScreenData()
{
}

WindowAPIData::WindowAPIData()
{
}

Window_API::WindowAPIData::~WindowAPIData()
{
}

Window_API_Structures::ScreenData Window_API::WindowAPIData::reload()
{
	screendata = Window_API_Structures::ScreenData(); // refreshes the data by constructor.
	return screendata;
}

v4 Global_Window_API_EnviromentVariables::WindowBackgroundColor = v4(0,0,0,1); // color of the background on OpenGL;


bool Window_API_Functions::shouldNotClose()
{
	return !glfwWindowShouldClose(winGB::ActiveWindowPTR);
}

// clears the buffer bits and refreshes the background coloring
void Window_API_Functions::clearBuffer()
{
	using namespace Global_Window_API_EnviromentVariables;
	glClearColor(WindowBackgroundColor.x, WindowBackgroundColor.y, WindowBackgroundColor.z, WindowBackgroundColor.w); // set the colors for the background.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the Buffer bits.
}

// polls for updates to the GLFW API and swaps draw buffers
void Window_API_Functions::eventQuery()
{
	glfwSwapBuffers(winGB::ActiveWindowPTR); // swap the draw buffers
	glfwPollEvents(); // check for input events.
}

void Window_API::Window_API_Functions::setMousePosition(double x, double y)
{
	glfwSetCursorPos(winGB::ActiveWindowPTR, x, y);
}
