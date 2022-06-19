#include "GUI.hpp"

using namespace GuiDefinition;
using namespace TopBarDefinition;
using namespace ToolbarDefinition;
using namespace CameraNavDefinition;
using namespace MeshToolsWindowDefinition;
using namespace ToolsWindowDefinition;


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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}


void GuiDefinition::GUI::buildGuiFrame()
{
	topBar.build();
	toolbar.build();
	cameraNav.build();
	meshToolsWindow.build();
	toolsWindow.build();
}

void GuiDefinition::GUI::renderGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

