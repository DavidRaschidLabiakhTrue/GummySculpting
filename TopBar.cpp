#include "TopBar.hpp"

static int topBarHeight = 0;

using namespace MeshToolsWindowDefinition;
using namespace ToolsWindowDefinition;

static bool isOctreeSeen = false;

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
		if (ImGui::MenuItem("Load Mesh"))
		{
			
			nfdchar_t* inPath = NULL;
			nfdresult_t result = NFD_OpenDialog("gum,obj", NULL, &inPath);
			string path;
			
			if (result == NFD_ERROR)
			{
				// do nothing
			}
			else if (result == NFD_CANCEL)
			{
				// also do nothing
			}
			else
			{
				buildCommand.emplace_back("file");
				buildCommand.emplace_back("import");
				path = inPath;
				buildCommand.emplace_back(path);
				MainDirectiveDefinition::Directives.emplace_back(buildCommand);
			}
		}
		
		if (ImGui::MenuItem("Export Mesh")) {
			nfdchar_t* outPath = NULL;
			nfdresult_t result = NFD_SaveDialog("gum,obj,stl", NULL, &outPath);
			string path;

			if (result == NFD_ERROR)
			{
				// do nothing
			}
			else if (result == NFD_CANCEL)
			{
				// also do nothing
			}
			else
			{
				buildCommand.emplace_back("file");
				buildCommand.emplace_back("export");
				path = outPath;
				buildCommand.emplace_back(path);
				MainDirectiveDefinition::Directives.emplace_back(buildCommand);
			}
		}

		ImGui::MenuItem("-----------", "", false, false); //dummy

		ImGui::MenuItem("Preferences");

		if (ImGui::MenuItem("Exit"))
		{
			exit(0);
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Undo", "Ctrl+Z"))
		{
			MainDirectiveDefinition::Directives.push_back({ "mesh", "undo" });
		}
		if (ImGui::MenuItem("Redo", "Ctrl+Shift+Z"))
		{
			MainDirectiveDefinition::Directives.push_back({ "mesh", "redo" });
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View"))
	{
		if (ImGui::MenuItem("Mesh Tools","",meshToolsWindow.getWindowStatus()))
		{
			meshToolsWindow.toggleWindow();
			//MainDirectiveDefinition::Directives.push_back({ "settings", "toggle" });
		}
		if (ImGui::MenuItem("Brush Tools","",toolsWindow.getWindowStatus()))
		{
			toolsWindow.toggleWindow();
			//MainDirectiveDefinition::Directives.push_back({ "settings", "toggle" });
		}
		ImGui::MenuItem("-----------", "", false, false); //dummy
		if (ImGui::MenuItem("Visualize Octree","", isOctreeSeen))
		{
			isOctreeSeen = !isOctreeSeen;
			MainDirectiveDefinition::Directives.push_back({ "octree", "visualize" });
		}

		ImGui::MenuItem("-----------", "", false, false); //dummy
		ImGui::MenuItem("Reset Camera");

		if (ImGui::MenuItem("Toggle Wireframe"))
		{
			MainDirectiveDefinition::Directives.push_back({ "renderer",  "toggle", "wireframe" });
		}

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