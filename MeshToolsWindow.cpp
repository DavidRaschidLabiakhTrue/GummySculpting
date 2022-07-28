#include "MeshToolsWindow.hpp"

static float buttonHeight = 30;
static float buttonWidth = 80;
static float buttonWidth2 = 124;
static float buttonWidth3 = 256;

namespace MeshToolsWindowDefinition
{
	static bool windowIsOpen = true;
}

MeshToolsWindowDefinition::MeshToolsWindow::MeshToolsWindow()
{
}
MeshToolsWindowDefinition::MeshToolsWindow::~MeshToolsWindow()
{
}

void insertButtonStyle()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255)));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(13, 125, 184)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(13, 100, 150)));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(150, 20, 20)));
}

void deleteButtonStyle()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255)));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(150, 20, 20)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(130, 20, 20)));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0)));
}

void loadMeshFromButton(string path)
{
	vector<string> buildCommand;
	buildCommand.emplace_back("file");
	buildCommand.emplace_back("import");
	buildCommand.emplace_back(path);
	MainDirectiveDefinition::Directives.emplace_back(buildCommand);
}

void MeshToolsWindowDefinition::MeshToolsWindow::build()
{
	ImGui::SetNextWindowSize(ImVec2(275, 240));

	ImGuiWindowFlags window_flags = 0
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoScrollbar
		| ImGuiWindowFlags_NoCollapse
		;

	if (windowIsOpen)
	{
		if (!ImGui::Begin("Mesh Tools", &windowIsOpen, window_flags))
		{
			ImGui::End();
		}
		else
		{
			ImGui::LabelText("", "Insert");
			insertButtonStyle();
			if (ImGui::Button("Bear", ImVec2(buttonWidth, buttonHeight)))
			{
				loadMeshFromButton("./Bear.gum");			
			}
			ImGui::PopStyleColor(4);
			ImGui::SameLine();
			insertButtonStyle();
			if (ImGui::Button("Sphere", ImVec2(buttonWidth, buttonHeight)))
			{
				loadMeshFromButton("./sphere.gum");
			}
			ImGui::PopStyleColor(4);
			ImGui::SameLine();
			insertButtonStyle();
			if (ImGui::Button("Cube", ImVec2(buttonWidth, buttonHeight)))
			{
				loadMeshFromButton("./cube.gum");
			}
			ImGui::PopStyleColor(4);
			insertButtonStyle();
			if (ImGui::Button("Plane", ImVec2(buttonWidth, buttonHeight)))
			{
				loadMeshFromButton("./plane.gum");
			}
			ImGui::PopStyleColor(4);
			ImGui::SameLine();
			insertButtonStyle();
			if (ImGui::Button("Arrow", ImVec2(buttonWidth, buttonHeight)))
			{
				loadMeshFromButton("./arrow.gum");
			}
			ImGui::PopStyleColor(4);
			ImGui::SameLine();
			insertButtonStyle();
			if (ImGui::Button("Ring", ImVec2(buttonWidth, buttonHeight)))
			{
				loadMeshFromButton("./ring.gum");
			}
			ImGui::PopStyleColor(4);
			ImGui::LabelText("", "Other");
			insertButtonStyle();
			if (ImGui::Button("Select Mesh", ImVec2(buttonWidth2, buttonHeight)))
			{
				MainDirectiveDefinition::Directives.push_back({ "sculptor", "select" });
			}
			ImGui::PopStyleColor(4);
			ImGui::SameLine();
			insertButtonStyle();
			if (ImGui::Button("Toggle WireFrame", ImVec2(buttonWidth2, buttonHeight)))
			{
				MainDirectiveDefinition::Directives.push_back({ "renderer",  "toggle", "wireframe" });
			}
			ImGui::PopStyleColor(4);
			ImGui::Dummy(ImVec2(0.f, 0.5f));
			deleteButtonStyle();
			if (ImGui::Button("Delete Selected Mesh", ImVec2(buttonWidth3, buttonHeight)))
			{
				MainDirectiveDefinition::Directives.push_back({ "renderer", "deleteCurrent" });
			}
			ImGui::PopStyleColor(4);
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
