#include "ToolsWindow.hpp"

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
	static float rgba[4] = { 0,0,0,0 };

	ImGui::Begin("Tools", nullptr, ImGuiWindowFlags_NoCollapse);

	ImGui::SliderFloat("Float Slider", &floatSlider, 0.f, 50.f); //Title TBA
	ImGui::SliderInt("Integer Slider", &integerSlider, 0, 100); //Title TBA
	ImGui::ColorEdit4("Color Picker", rgba); //Title TBA

	ImGui::End();
}
