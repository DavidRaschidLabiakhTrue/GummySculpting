#include "KeyInput.hpp"
Usage WindowGlobal;
Usage KeyInputDefinition;


bool KeyInputDefinition::CheckIfAnyKeyHeld()
{
	struct funcs { static bool IsLegacyNativeDupe(ImGuiKey key) { return key < 512 && ImGui::GetIO().KeyMap[key] != -1; } }; // Hide Native<>ImGuiKey duplicates when both exists in the array
	const ImGuiKey key_first = 0;
	for (ImGuiKey key = key_first; key < ImGuiKey_COUNT; key++) 
	{ 
		if (funcs::IsLegacyNativeDupe(key))
		{
			continue;
		}
		if (ImGui::IsKeyDown(key))
		{
			return true;
		} 
	}
	return false;
}

bool KeyInputDefinition::isHeld(KeyInputCode keycode)
{
	
	switch (keycode)
	{
		case Key_A:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_A) == GLFW_PRESS;
		case Key_B:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_B) == GLFW_PRESS;
		case Key_C:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_C) == GLFW_PRESS;
		case Key_D:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_D) == GLFW_PRESS;
		case Key_E:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_E) == GLFW_PRESS;
		case Key_F:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_F) == GLFW_PRESS;
		case Key_G:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_G) == GLFW_PRESS;
		case Key_H:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_H) == GLFW_PRESS;
		case Key_I:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_I) == GLFW_PRESS;
		case Key_J:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_J) == GLFW_PRESS;
		case Key_K:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_K) == GLFW_PRESS;
		case Key_L:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_L) == GLFW_PRESS;
		case Key_M:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_M) == GLFW_PRESS;
		case Key_N:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_N) == GLFW_PRESS;
		case Key_O:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_O) == GLFW_PRESS;
		case Key_P:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_P) == GLFW_PRESS;
		case Key_Q:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_Q) == GLFW_PRESS;
		case Key_R:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_R) == GLFW_PRESS;
		case Key_S:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_S) == GLFW_PRESS;
		case Key_T:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_T) == GLFW_PRESS;
		case Key_U:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_U) == GLFW_PRESS;
		case Key_V:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_V) == GLFW_PRESS;
		case Key_W:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_W) == GLFW_PRESS;
		case Key_X:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_X) == GLFW_PRESS;
		case Key_Y:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_Y) == GLFW_PRESS;
		case Key_Z:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_Z) == GLFW_PRESS;
		case Key_1:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_1) == GLFW_PRESS;
		case Key_2:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_2) == GLFW_PRESS;
		case Key_3:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_3) == GLFW_PRESS;
		case Key_4:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_4) == GLFW_PRESS;
		case Key_5:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_5) == GLFW_PRESS;
		case Key_6:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_6) == GLFW_PRESS;
		case Key_7:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_7) == GLFW_PRESS;
		case Key_8:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_8) == GLFW_PRESS;
		case Key_9:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_9) == GLFW_PRESS;
		case Key_0:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_0) == GLFW_PRESS;
		case Key_minus:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_MINUS) == GLFW_PRESS;
		case Key_plus:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_EQUAL) == GLFW_PRESS;
		case Key_backspace:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_BACKSPACE ) == GLFW_PRESS;
		case Key_up:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_UP) == GLFW_PRESS;
		case Key_down:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_DOWN ) == GLFW_PRESS;
		case Key_left:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_LEFT ) == GLFW_PRESS;
		case Key_right:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_RIGHT ) == GLFW_PRESS;
		case Key_space:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_SPACE ) == GLFW_PRESS;
		case Key_control:
			return (glfwGetKey(ActiveWindowPTR, GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS);
		case Key_alt:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_LEFT_ALT ) == GLFW_PRESS;
		case Key_caps:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS;
		case Key_shift:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS;
		case Key_period:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_PERIOD ) == GLFW_PRESS;
		case Key_comma:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_COMMA ) == GLFW_PRESS;
		case Key_slashRightForward:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_SLASH) == GLFW_PRESS;
		case Key_slashLeftBackward:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_BACKSLASH) == GLFW_PRESS;
		case Key_tab:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_TAB ) == GLFW_PRESS;
		case Key_tilde:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS;
		case Key_enter:
			return glfwGetKey(ActiveWindowPTR, GLFW_KEY_ENTER) == GLFW_PRESS;
	}
    return false;
}

bool KeyInputDefinition::isNotHeld(KeyInputCode keycode)
{

	switch (keycode)
	{
	case Key_A:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_A) == GLFW_RELEASE;
	case Key_B:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_B) == GLFW_RELEASE;
	case Key_C:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_C) == GLFW_RELEASE;
	case Key_D:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_D) == GLFW_RELEASE;
	case Key_E:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_E) == GLFW_RELEASE;
	case Key_F:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_F) == GLFW_RELEASE;
	case Key_G:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_G) == GLFW_RELEASE;
	case Key_H:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_H) == GLFW_RELEASE;
	case Key_I:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_I) == GLFW_RELEASE;
	case Key_J:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_J) == GLFW_RELEASE;
	case Key_K:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_K) == GLFW_RELEASE;
	case Key_L:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_L) == GLFW_RELEASE;
	case Key_M:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_M) == GLFW_RELEASE;
	case Key_N:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_N) == GLFW_RELEASE;
	case Key_O:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_O) == GLFW_RELEASE;
	case Key_P:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_P) == GLFW_RELEASE;
	case Key_Q:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_Q) == GLFW_RELEASE;
	case Key_R:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_R) == GLFW_RELEASE;
	case Key_S:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_S) == GLFW_RELEASE;
	case Key_T:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_T) == GLFW_RELEASE;
	case Key_U:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_U) == GLFW_RELEASE;
	case Key_V:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_V) == GLFW_RELEASE;
	case Key_W:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_W) == GLFW_RELEASE;
	case Key_X:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_X) == GLFW_RELEASE;
	case Key_Y:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_Y) == GLFW_RELEASE;
	case Key_Z:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_Z) == GLFW_RELEASE;
	case Key_1:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_1) == GLFW_RELEASE;
	case Key_2:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_2) == GLFW_RELEASE;
	case Key_3:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_3) == GLFW_RELEASE;
	case Key_4:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_4) == GLFW_RELEASE;
	case Key_5:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_5) == GLFW_RELEASE;
	case Key_6:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_6) == GLFW_RELEASE;
	case Key_7:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_7) == GLFW_RELEASE;
	case Key_8:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_8) == GLFW_RELEASE;
	case Key_9:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_9) == GLFW_RELEASE;
	case Key_0:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_0) == GLFW_RELEASE;
	case Key_minus:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_MINUS) == GLFW_RELEASE;
	case Key_plus:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_EQUAL) == GLFW_RELEASE;
	case Key_backspace:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_BACKSPACE) == GLFW_RELEASE;
	case Key_up:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_UP) == GLFW_RELEASE;
	case Key_down:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_DOWN) == GLFW_RELEASE;
	case Key_left:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_LEFT) == GLFW_RELEASE;
	case Key_right:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_RIGHT) == GLFW_RELEASE;
	case Key_space:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_SPACE) == GLFW_RELEASE;
	case Key_control:
		return (glfwGetKey(ActiveWindowPTR, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE);
	case Key_alt:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE;
	case Key_caps:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_CAPS_LOCK) == GLFW_RELEASE;
	case Key_shift:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE;
	case Key_period:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_PERIOD) == GLFW_RELEASE;
	case Key_comma:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_COMMA) == GLFW_RELEASE;
	case Key_slashRightForward:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_SLASH) == GLFW_RELEASE;
	case Key_slashLeftBackward:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_BACKSLASH) == GLFW_RELEASE;
	case Key_tab:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_TAB) == GLFW_RELEASE;
	case Key_tilde:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE;
	case Key_enter:
		return glfwGetKey(ActiveWindowPTR, GLFW_KEY_ENTER) == GLFW_RELEASE;
	}
	return false;
	
}

bool KeyInputDefinition::isPressed(int keycode)
{
	if (find(inputBuffer.begin(), inputBuffer.end(), keycode) != inputBuffer.end())
	{
		return true;
	}
	return false;
}