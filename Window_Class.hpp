#ifndef WindowClass_HPP
#define WindowClass_HPP

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"


#include "OpenGLWrapper.hpp"

#include "GLFW/glfw3.h"

#include "Macro.hpp"

#include "MathDefinitions.hpp"

#include "mini/ini.h"

#define DEFAULT_openglVersionMajor 4
#define DEFAULT_openGLVersionMinor 6

namespace Window_Class
{
	Usage MathTypeDefinitions::CoordinateDefine;

	
	typedef GLFWwindow* WinPtr;

	// Window Class
	// Singleton in nature.
	class Window
	{
		public:
			Empty_Construct Window();
			Construct Window(bool trueConstructor);
			Deconstruct ~Window();

		Public_Variables

			int scroll_state = 0; // holds the scroll state.
			bool canRender = true;
		private:
			
			
			void setGFLWCallBacks(); // load GLFW Callbacks
			void loadGLFWToProgram(); // load GLFW
			void LoadOpenGL(); // load GLAD
			WinPtr winptr = UnassignedPTR;
			
			v2 dim;
	};


	namespace Window_CallBackFunctions
	{
		extern void framebuffer_size_callback(GLFWwindow* win, int width, int height); /// window resize call back


		extern void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // mouse wheel scroll call back



	}

	namespace WindowGlobal
	{
		extern Window* ActiveWindow;
		extern WinPtr ActiveWindowPTR; // the window ptr everything else may access.
	}
	namespace winGB = WindowGlobal;
}


#endif
