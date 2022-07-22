#include "CameraNav.hpp"

static float widgetSideLength = 150;
static float ButtonSideLength = 40;

CameraNavDefinition::CameraNav::CameraNav()
{
}

CameraNavDefinition::CameraNav::~CameraNav()
{
}


void buttonStyle()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255)));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(13, 125, 184)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(13, 100, 150)));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(150, 20, 20)));
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
	buttonStyle();
	ImGui::Button("^", ImVec2(ButtonSideLength, ButtonSideLength));
	ImGui::PopStyleColor(4);
	ImGui::Dummy(ImVec2(0.f, 0.5f));
	buttonStyle();
	ImGui::Button("<", ImVec2(ButtonSideLength, ButtonSideLength));
	ImGui::PopStyleColor(4);
	ImGui::SameLine();
	ImGui::Dummy(ImVec2((float)ButtonSideLength-1, 0.f));
	ImGui::SameLine();
	buttonStyle();
	ImGui::Button(">", ImVec2(ButtonSideLength, ButtonSideLength));
	ImGui::PopStyleColor(4);
	ImGui::Dummy(ImVec2(0.f, 0.5f));
	ImGui::Dummy(ImVec2((float)ButtonSideLength-1, 0.f));
	ImGui::SameLine();
	buttonStyle();
	ImGui::Button("v", ImVec2(ButtonSideLength, ButtonSideLength));
	ImGui::PopStyleColor(4);
	ImGui::End();
}
