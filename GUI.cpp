#include "GUI.hpp"

using namespace GuiDefinition;


GUI::GUI()
{
	
}

GuiDefinition::GUI::GUI(bool trueConstructor)
{
	this->imguiIO = InitializeImGUI();
}

GUI::~GUI()
{

}

void GuiDefinition::GUI::newGuiFrame()
{

}

void GuiDefinition::GUI::buildGuiFrame()
{
}

void GuiDefinition::GUI::renderGui()
{
}



ImGuiIO& GuiDefinition::InitializeImGUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(WindowGlobal::ActiveWindowPTR, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	say "ImGUI fully Initialized" done;

	return io;
}

