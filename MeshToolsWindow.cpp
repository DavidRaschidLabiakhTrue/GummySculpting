#include "MeshToolsWindow.hpp"

namespace MeshToolsWindowDefinition
{
	static bool windowIsOpen = false;
}

MeshToolsWindowDefinition::MeshToolsWindow::MeshToolsWindow()
{
}
MeshToolsWindowDefinition::MeshToolsWindow::~MeshToolsWindow()
{
}

void MeshToolsWindowDefinition::MeshToolsWindow::build()
{
	static float floatSlider1 = 0.f;	//Edit Here
	static float floatSlider2 = 0.f;	//Edit Here
	static int integerSlider1 = 0;		//Edit Here	
	static int integerSlider2 = 0;		//Edit Here
	static bool checkbox1 = false;		//Edit Here
	static bool checkbox2 = false;		//Edit Here
	static bool checkbox3 = false;		//Edit Here
	static bool checkbox4 = false;		//Edit Here

	if (windowIsOpen)
	{
		if (!ImGui::Begin("Mesh Tools", &windowIsOpen, ImGuiWindowFlags_NoCollapse))
		{
			ImGui::End();
		}
		else
		{
			ImGui::LabelText("", "Slider Tools");
			ImGui::SliderFloat("Float Slider Title 1", &floatSlider1, 0.f, 0.1f); 
			ImGui::SliderFloat("Float Slider Title 2", &floatSlider2, 0.f, 0.1f);
			ImGui::SliderInt("Integer Slider Title 1", &integerSlider1, 0, 100);
			ImGui::SliderInt("Integer Slider Title 2", &integerSlider2, 0, 100);
			ImGui::LabelText("","Boolean Input");
			ImGui::Checkbox("Checkbox 1", &checkbox1);
			ImGui::SameLine();
			ImGui::Checkbox("Checkbox 2", &checkbox2);
			ImGui::Checkbox("Checkbox 3", &checkbox3);
			ImGui::SameLine();
			ImGui::Checkbox("Checkbox 4", &checkbox4);
			ImGui::SameLine();
		
			ImGui::End();
		}
	}

}

void MeshToolsWindowDefinition::MeshToolsWindow::toggleWindow()
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

bool MeshToolsWindowDefinition::MeshToolsWindow::getWindowStatus()
{
	return windowIsOpen;
}
