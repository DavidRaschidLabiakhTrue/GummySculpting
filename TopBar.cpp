#include "TopBar.hpp"

TopBarDefinition::TopBar::TopBar()
{
}

TopBarDefinition::TopBar::~TopBar()
{
}

void TopBarDefinition::TopBar::build()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		ImGui::MenuItem("Load Mesh");
		ImGui::MenuItem("Export Mesh");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::MenuItem("Undo");
		ImGui::MenuItem("Redo");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View"))
	{
		ImGui::MenuItem("Reset Camera");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Settings"))
	{
		ImGui::MenuItem("Advanced Settings");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Help"))
	{
		if (ImGui::MenuItem("Debug Console"))
		{
			vector<string> debugToggleCommand = { "debug",  "toggle" };
			MainDirectiveDefinition::Directives.push_back(debugToggleCommand);
		}
		
		ImGui::MenuItem("Help Guide");
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}
