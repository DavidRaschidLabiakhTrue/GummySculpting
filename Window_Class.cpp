#include "Window_Class.hpp"

namespace Window_Class
{
	// globals for the window, largely singleton only.
	namespace WindowGlobal
	{
		Window* ActiveWindow = UnassignedPTR;
		WinPtr ActiveWindowPTR = UnassignedPTR;
		InputBuffer inputBuffer = InputBuffer();
	}

	// implementation of GLFW callback functions.
	namespace Window_CallBackFunctions
	{
		void framebuffer_size_callback(GLFWwindow* win, int width, int height)
		{
			WindowGlobal::ActiveWindow->canRender = (width == 0 or height == 0) ? false : true;

			glViewport(0, 0, width, height);
		}

		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowGlobal::ActiveWindow->scroll_val = yoffset;
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{

				WindowGlobal::inputBuffer.push_back(key);

			}
		}
	}
	

}


Usage Window_Class;
void Window::loadGLFWToProgram()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (DEFAULT_openglVersionMajor)); // Version 4.6, the latest
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, (DEFAULT_openGLVersionMinor));
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // get core profile, aka basic functions loaded for use in GPU/Graphics Processor.
	glfwWindowHint(GLFW_SAMPLES, 4); // anti aliasing
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE); // doubles up the buffer
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); // this loads up full screen for us. Not giving users the ability to resize the screen.
	

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor()); // get dimensions of monitor automatically.

	dim.x = mode->width;
	dim.y = mode->height;


	winptr = glfwCreateWindow(dim.x, dim.y, "Gummy!", NULL, NULL); // load the window pointer

	WindowGlobal::ActiveWindowPTR = winptr; // attach ptr to global usage.

	ifn(winptr)
	{
		// implement broadcast
	}

	setGFLWCallBacks();


	glfwMakeContextCurrent(winptr);

	

}

Window_Class::Window::Window()
{
}

Window::Window(bool trueConstructor)
{
	loadGLFWToProgram();
	LoadOpenGL();
}
Window::~Window()
{

}

void Window_Class::Window::cleanUp()
{
	glfwDestroyWindow(this->winptr);
	glfwTerminate();
}

void Window::setGFLWCallBacks()
{
	glfwSetFramebufferSizeCallback(winptr, Window_CallBackFunctions::framebuffer_size_callback);
	glfwSetScrollCallback(winptr, Window_CallBackFunctions::scroll_callback);
	glfwSetKeyCallback(winptr, Window_CallBackFunctions::key_callback);
}



void Window::LoadOpenGL()
{
	gladLoadGL();
	GL::set3DRenderingParameters();
	GL::printOpenGLEnviromentInfo();
}



