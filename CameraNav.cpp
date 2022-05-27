#include "CameraNav.hpp"

static int widgetSideLength = 150;
static int ButtonSideLength = 40;

CameraNavDefinition::CameraNav::CameraNav()
{
}

CameraNavDefinition::CameraNav::~CameraNav()
{
}

void CameraNavDefinition::CameraNav::build()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x + 50, viewport->Size.y - 50 - widgetSideLength));
	ImGui::SetNextWindowSize(ImVec2(widgetSideLength, widgetSideLength));

	vector<string> buildMessage;

	ImGuiWindowFlags window_flags = 0
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoScrollbar
		| ImGuiWindowFlags_NoSavedSettings
		;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin("CameraNav", NULL, window_flags);
	ImGui::PopStyleVar();

	ImGui::Dummy(ImVec2((float)ButtonSideLength-1, 0.f));
	ImGui::SameLine();
	ImGui::Button("^", ImVec2(ButtonSideLength, ButtonSideLength));
	ImGui::Dummy(ImVec2(0.f, 0.5f));
	ImGui::Button("<", ImVec2(ButtonSideLength, ButtonSideLength));
	ImGui::SameLine();
	ImGui::Dummy(ImVec2((float)ButtonSideLength-1, 0.f));
	ImGui::SameLine();
	ImGui::Button(">", ImVec2(ButtonSideLength, ButtonSideLength));
	ImGui::Dummy(ImVec2(0.f, 0.5f));
	ImGui::Dummy(ImVec2((float)ButtonSideLength-1, 0.f));
	ImGui::SameLine();
	ImGui::Button("v", ImVec2(ButtonSideLength, ButtonSideLength));

	ImGui::End();
}