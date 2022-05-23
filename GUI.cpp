#include "GUI.hpp"

using namespace GuiDefinition;
using namespace TopBarDefinition;


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

void ToolsWindow()
{
	//Use/replace these 3 vars with whatever you want to implement
	static float floatSlider = 0.f;
	static int integerSlider = 0;
	static float rgba[4] = { 0,0,0,0 };

	ImGui::Begin("Tools", nullptr, ImGuiWindowFlags_NoCollapse);

	ImGui::SliderFloat("Float Slider", &floatSlider, 0.f, 50.f); //Title TBA
	ImGui::SliderInt("Integer Slider", &integerSlider, 0, 100); //Title TBA
	ImGui::ColorEdit4("Color Picker", rgba); //Title TBA

	ImGui::End();
}

void GuiDefinition::GUI::buildGuiFrame()
{
	ToolsWindow();
	topBar.build();
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

