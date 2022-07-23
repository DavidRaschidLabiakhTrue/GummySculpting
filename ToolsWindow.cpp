#include "ToolsWindow.hpp"

namespace ToolsWindowDefinition
{
	static bool windowIsOpen = true;
	v4 ColorSlider_Color_Values = v4(0,1,0,1);
	float RadiusSlider = 0.25f;
}

ToolsWindowDefinition::ToolsWindow::ToolsWindow()
{
}

ToolsWindowDefinition::ToolsWindow::~ToolsWindow()
{
}

void ToolsWindowDefinition::ToolsWindow::build()
{
	static float floatSlider = 1.0f;
	static int integerSlider = 0;
	static float rgba[4] = { 0.5, 0.5, 0.5, 1.0f };
	static bool checkbox1 = false;		//Edit Here
	static bool checkbox2 = false;		//Edit Here
	static bool checkbox3 = false;		//Edit Here
	static bool checkbox4 = false;		//Edit Here

	ImGui::SetNextWindowSize(ImVec2(330, 380));

	ImGuiWindowFlags window_flags = 0
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoScrollbar
		;

	if (windowIsOpen) 
	{
		if (!ImGui::Begin("Brush Tools", &windowIsOpen, window_flags))
		{
			ImGui::End();
		}
		else
		{
			ImGui::LabelText("", "Brush Size");
			ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(ImColor(13, 125, 184)));
			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(ImColor(150, 20, 20)));
			ImGui::SliderFloat(" ", &floatSlider, 0.f,2.0f);
			ImGui::PopStyleColor(2);
			ImGui::LabelText("", "Brush Color");
			ImGui::ColorPicker3("", rgba);

			ColorSlider_Color_Values[0] = rgba[0] != 0 ? rgba[0] : ColorSlider_Color_Values[0];
			ColorSlider_Color_Values[1] = rgba[1] != 0 ? rgba[1] : ColorSlider_Color_Values[1];
			ColorSlider_Color_Values[2] = rgba[2] != 0 ? rgba[2] : ColorSlider_Color_Values[2];
			ColorSlider_Color_Values[3] = 1.0f; // Alpha is *always* on

			RadiusSlider = (floatSlider != RadiusSlider) ? floatSlider : RadiusSlider;

			ImGui::End();
		}
	}
}

void ToolsWindowDefinition::ToolsWindow::toggleWindow()
{
	if (windowIsOpen)
	{
		windowIsOpen = false;
	}
	else
	{
		windowIsOpen = true;
	}
}

bool ToolsWindowDefinition::ToolsWindow::getWindowStatus()
{
	return windowIsOpen;
}