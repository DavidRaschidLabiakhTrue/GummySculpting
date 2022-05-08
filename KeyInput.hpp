#ifndef KeyInput_HPP
#define KeyInput_HPP

#include "Window_API.hpp"

Usage Window_API;

namespace KeyInputDefinition
{

	#define CheckKeyPressed(x) glfwGetKey(WindowGlobal::ActiveWindowPTR, (x) ) == GLFW_PRESS
	#define CheckMousePressed(x) glfwGetMouseButton(WindowGlobal::ActiveWindowPTR, (x) ) == GLFW_PRESS

	#define CheckKeyReleased(x) glfwGetKey(WindowGlobal::ActiveWindowPTR, (x) ) == GLFW_RELEASE
	#define CheckMouseReleased(x) glfwGetMouseButton(WindowGlobal::ActiveWindowPTR, (x) ) == GLFW_RELEASE


	enum KeyInputCode
	{
		Key_A, 
		Key_B, 
		Key_C, 
		Key_D, 
		Key_E, 
		Key_F, 
		Key_G, 
		Key_H, 
		Key_I, 
		Key_J, 
		Key_K, 
		Key_L, 
		Key_M, 
		Key_N, 
		Key_O, 
		Key_P, 
		Key_Q, 
		Key_R, 
		Key_S, 
		Key_T, 
		Key_U, 
		Key_V, 
		Key_W, 
		Key_X, 
		Key_Y, 
		Key_Z, 
		Key_1, 
		Key_2, 
		Key_3, 
		Key_4, 
		Key_5, 
		Key_6, 
		Key_7, 
		Key_8, 
		Key_9, 
		Key_0, 
		Key_minus, 
		Key_plus, 
		Key_backspace,
		Key_up, 
		Key_down, 
		Key_left, 
		Key_right, 
		Key_space, 
		Key_control, 
		Key_alt, 
		Key_caps, 
		Key_shift, 
		Key_period, 
		Key_comma, 
		Key_slashRightForward,  
		Key_slashLeftBackward, 
		Key_tab, 
		Key_tilde,
		Key_enter
	};

	
	extern bool isPressed(KeyInputCode keycode); // succint way of checking for k input without touching GLFW
	extern bool isNotPressed(KeyInputCode keycode);
}

#endif
