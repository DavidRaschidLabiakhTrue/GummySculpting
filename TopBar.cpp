#include "TopBar.hpp"

static int topBarHeight = 0;

TopBarDefinition::TopBar::TopBar()
{
}

TopBarDefinition::TopBar::~TopBar()
{
}

void TopBarDefinition::TopBar::build()
{
	vector<string> buildCommand;
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		ImGui::MenuItem("Load Mesh");
		ImGui::MenuItem("Export Mesh");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Undo"))
		{
			MainDirectiveDefinition::Directives.push_back({ "mesh", "undo" });
		}
		if (ImGui::MenuItem("Redo"))
		{
			MainDirectiveDefinition::Directives.push_back({ "mesh", "redo" });
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View"))
	{
		ImGui::MenuItem("Reset Camera");

		if (ImGui::MenuItem("Toggle Wireframe"))
		{
			MainDirectiveDefinition::Directives.push_back({ "renderer",  "toggle", "wireframe" });
		}

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
			MainDirectiveDefinition::Directives.push_back({ "debug",  "toggle" });
		}
		
		ImGui::MenuItem("Help Guide");
		ImGui::EndMenu();
	}
	topBarHeight = ImGui::GetWindowHeight();
	ImGui::EndMainMenuBar();
}

int TopBarDefinition::TopBar::getHeight()
{
	return topBarHeight;
}