#include "Toolbar.hpp"

using namespace TopBarDefinition;

static float toolbarHeight = 45;
static float buttonHeight = 30;

ToolbarDefinition::Toolbar::Toolbar()
{
}

ToolbarDefinition::Toolbar::~Toolbar()
{
}

void ToolbarDefinition::Toolbar::build()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + topBar.getHeight()));
	ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, toolbarHeight));



	ImGuiWindowFlags window_flags = 0
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoScrollbar
		| ImGuiWindowFlags_NoSavedSettings
		;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin("TOOLBAR", NULL, window_flags);
	ImGui::PopStyleVar();

	if (ImGui::Button("Stroke Brush", ImVec2(0, buttonHeight)))
	{

		MainDirectiveDefinition::Directives.push_back({ "sculptor", "stroke" });
	}
	ImGui::SameLine();
	if (ImGui::Button("Smooth Brush", ImVec2(0, buttonHeight)))
	{

		MainDirectiveDefinition::Directives.push_back({ "sculptor", "smooth" });
	};
	ImGui::SameLine();
	if (ImGui::Button("Color Brush", ImVec2(0, buttonHeight)))
	{

		MainDirectiveDefinition::Directives.push_back({ "sculptor", "color" });
	};
	ImGui::SameLine();


	if (ImGui::Button("Smoothed Color Brush", ImVec2(0, buttonHeight)))
	{

		MainDirectiveDefinition::Directives.push_back({ "sculptor", "smoothedcolor" });
	};
	ImGui::SameLine();

	if (ImGui::Button("Noise Brush", ImVec2(0, buttonHeight)))
	{

		MainDirectiveDefinition::Directives.push_back({ "sculptor", "noise" });
	}

	ImGui::SameLine();

	if (ImGui::Button("Simple Subdivide", ImVec2(0, buttonHeight)))
	{

		MainDirectiveDefinition::Directives.push_back({ "mesh", "simplesubdivide", "1" });
	}
	ImGui::SameLine();

	if (ImGui::Button("Loop Subdivide", ImVec2(0, buttonHeight)))
	{

		MainDirectiveDefinition::Directives.push_back({ "mesh", "loopsubdivide", "1" });
	}


	ImGui::End();
}