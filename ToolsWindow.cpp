#include "ToolsWindow.hpp"

namespace ToolsWindowDefinition
{
	v4 ColorSlider_Color_Values = v4(0,1,0,1);
}

ToolsWindowDefinition::ToolsWindow::ToolsWindow()
{
}

ToolsWindowDefinition::ToolsWindow::~ToolsWindow()
{
}

void ToolsWindowDefinition::ToolsWindow::build()
{
	//Use/replace these 3 vars with whatever you want to implement
	static float floatSlider = 0.f;
	static int integerSlider = 0;
	static float rgba[4] = { 0.5, 0.5, 0.5, 1.0f };

	ImGui::Begin("Tools", nullptr, ImGuiWindowFlags_NoCollapse);

	ImGui::SliderFloat("Float Slider", &floatSlider, 0.f, 50.f); //Title TBA
	ImGui::SliderInt("Integer Slider", &integerSlider, 0, 100); //Title TBA
	ImGui::ColorEdit4("Color Picker", rgba); //Title TBA


	ColorSlider_Color_Values[0] = rgba[0] != 0 ? rgba[0] : ColorSlider_Color_Values[0];
	ColorSlider_Color_Values[1] = rgba[1] != 0 ? rgba[1] : ColorSlider_Color_Values[1];
	ColorSlider_Color_Values[2] = rgba[2] != 0 ? rgba[2] : ColorSlider_Color_Values[2];
	ColorSlider_Color_Values[3] = 1.0f; // Alpha is *always* on

	ImGui::End();
}
