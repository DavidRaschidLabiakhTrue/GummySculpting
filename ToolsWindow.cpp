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

	if (windowIsOpen) 
	{
		if (!ImGui::Begin("Brush Tools", &windowIsOpen, ImGuiWindowFlags_NoCollapse))
		{
			ImGui::End();
		}
		else
		{
			ImGui::LabelText("", "Size");
			ImGui::SliderFloat("Brush Radius Slider", &floatSlider, 0.f,2.0f);
			ImGui::SliderInt("Integer Slider", &integerSlider, 0, 100);
			ImGui::LabelText("", "Color");
			ImGui::ColorEdit4("Color Picker", rgba);

			ImGui::LabelText("", "Boolean Input");
			ImGui::Checkbox("Checkbox 1", &checkbox1);
			ImGui::SameLine();
			ImGui::Checkbox("Checkbox 2", &checkbox2);
			ImGui::Checkbox("Checkbox 3", &checkbox3);
			ImGui::SameLine();
			ImGui::Checkbox("Checkbox 4", &checkbox4);
			ImGui::SameLine();

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