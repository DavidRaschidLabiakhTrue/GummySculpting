#include "Toolbar.hpp"

using namespace TopBarDefinition;

static int toolbarHeight = 45;
static int buttonHeight = 30;

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

	ImGui::Button("Color Brush", ImVec2(0, buttonHeight));
	ImGui::SameLine();
	ImGui::Button("Smooth Brush", ImVec2(0, buttonHeight));
	ImGui::SameLine();
	ImGui::Button("Stroke Brush", ImVec2(0, buttonHeight));
	ImGui::SameLine();

	ImGui::End();
}