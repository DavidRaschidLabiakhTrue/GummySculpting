#include<windows.h>
#include "Toolbar.hpp"

using namespace TopBarDefinition;

static unsigned int buttonDelay = 3000; // 3 seconds

static float toolbarHeight = 65;
static float buttonHeight = 30;
static float buttonWidth1 = 80;
static float buttonWidth2 = 150;
static float buttonWidth3 = 110;

static bool isStrokeToggled = false;
static bool isStrokeSmoothToggled = false;
static bool isSmoothToggled = false;
static bool isColorToggled = false;
static bool isSmoothedColorToggled = false;
static bool isNoiseToggled = false;
static bool isSimpleSubToggled = false;
static bool isLoopToggled = false;
static bool isTessellationToggled = false;
static bool isBrushToggled = false;
static bool isExtrudeToggled = false;
static bool isPullToggled = false;
static bool isDecimateToggled = false;
static bool isRemeshToggled = false;
static bool isOctreeToggled = false;
static bool isInflateToggled = false;
static bool isSelectorToggled = false;
ToolbarDefinition::Toolbar::Toolbar()
{
}

ToolbarDefinition::Toolbar::~Toolbar()
{
}

//================= CHANGE COLORS HERE =====================
void toggleTrue()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255)));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(150, 20, 20)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(150, 20, 20)));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0)));
}

void toggleFalse()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255)));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(13, 125, 184)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(13, 100, 150)));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(150, 20, 20)));
}
//=========================================================

void resetToggleButtons()
{
	isStrokeToggled = false;
	isStrokeSmoothToggled = false;
	isSmoothToggled = false;
	isColorToggled = false;
	isSmoothedColorToggled = false;
	isNoiseToggled = false;
	isSimpleSubToggled = false;
	isLoopToggled = false;
	isTessellationToggled = false;
	isBrushToggled = false;
	isExtrudeToggled = false;
	isPullToggled = false;
	isDecimateToggled = false;
	isRemeshToggled = false;
	isOctreeToggled = false;
	isInflateToggled = false;
	isSelectorToggled = false;
}

void StrokeToggleButton()
{
	int pushedColors = 0;

	if (isStrokeToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Clay", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
;		isStrokeToggled = !isStrokeToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "dirac" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Deform the surface of the mesh in a clay like manner");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void BrushToggleButton()
{
	int pushedColors = 0;

	if (isBrushToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Stroke", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
		isBrushToggled = !isBrushToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "brush" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Deform the mesh as if you are using a pen"); //CHANGE HERE
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void ExtrudeToggleButton()
{
	int pushedColors = 0;

	if (isExtrudeToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Extrude", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
		isExtrudeToggled = !isExtrudeToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "extrude" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Pull out the surface of the mesh uniformly");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void PullToggleButton()
{
	int pushedColors = 0;

	if (isPullToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Pull", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
		isPullToggled = !isPullToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "pull" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Pull out the surface of the mesh with decreasing surface area");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void StrokeSmoothToggleButton()
{
	int pushedColors = 0;

	if (isStrokeSmoothToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Stroke Smoothing", ImVec2(buttonWidth2, buttonHeight)))
	{
		resetToggleButtons();
		isStrokeSmoothToggled = !isStrokeSmoothToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "stroke" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Smooths deformation of the mesh");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void SmoothToggleButton()
{
	int pushedColors = 0;

	if (isSmoothToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Smooth", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
		isSmoothToggled = !isSmoothToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "smooth" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Smooths the surface of the mesh");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void ColorToggleButton()
{
	int pushedColors = 0;

	if (isColorToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Color", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
		isColorToggled = !isColorToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "color" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Adds color to the mesh");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void SmoothedColorToggleButton()
{
	int pushedColors = 0;

	if (isSmoothedColorToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Blend", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
		isSmoothedColorToggled = !isSmoothedColorToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "smoothedcolor" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Smooths the color(s) of the mesh");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void NoiseToggleButton()
{
	int pushedColors = 0;

	if (isNoiseToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Noise", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
		isNoiseToggled = !isNoiseToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "noise" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Randomly changes surface of the mesh");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void InflateToggleButton()
{
	int pushedColors = 0;

	if (isInflateToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Inflate", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
		isInflateToggled = !isInflateToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "inflate" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Inflates area of the mesh");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void TessellationToggleButton()
{
	int pushedColors = 0;
	if (isTessellationToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Tessellation", ImVec2(buttonWidth3, buttonHeight)))
	{
		resetToggleButtons();
		isTessellationToggled = !isTessellationToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "tessellate" });
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Adds resolution to selected area of the mesh");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void SimpleSubdivToggleButton()
{
	int pushedColors = 0;

	if (isSimpleSubToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Simple Subdivide", ImVec2(buttonWidth2, buttonHeight)))
	{
		isSimpleSubToggled = true;
		MainDirectiveDefinition::Directives.push_back({ "mesh", "simplesubdivide", "1" });
		// Sleep(buttonDelay);
		isSimpleSubToggled = false;
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Adds resolution to the entire mesh");
	}
	ImGui::PopStyleColor(pushedColors);

	ImGui::SameLine();
}


void loopToggleButton()
{
	int pushedColors = 0;

	if (isLoopToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Loop Subdivide", ImVec2(buttonWidth2, buttonHeight)))
	{
		isLoopToggled = true;
		MainDirectiveDefinition::Directives.push_back({ "mesh", "loopsubdivide", "1" });
		isLoopToggled = false;
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Adds resolution to the entire mesh without requiring mesh refinement");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}


void DecimationToggleButton()
{
	int pushedColors = 0;
	if (isDecimateToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Decimation", ImVec2(buttonWidth3, buttonHeight)))
	{
		isDecimateToggled = true;
		MainDirectiveDefinition::Directives.push_back({ "mesh", "decimate" });
		isDecimateToggled = false;
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Reduces mesh resolution");
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void RemeshToggleButton()
{
	int pushedColors = 0;
	if (isRemeshToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Remesh", ImVec2(buttonWidth1, buttonHeight)))
	{
		isRemeshToggled = true;
		// MainDirectiveDefinition::Directives.push_back({ "mesh", "remesh" });
		MainDirectiveDefinition::Directives.push_back({ "mesh", "loopsubdivide", "1" });
		MainDirectiveDefinition::Directives.push_back({ "mesh", "decimate" });
		MainDirectiveDefinition::Directives.push_back({ "mesh", "decimate" });
		MainDirectiveDefinition::Directives.push_back({ "mesh", "decimate" });
		MainDirectiveDefinition::Directives.push_back({ "mesh", "decimate" });
		MainDirectiveDefinition::Directives.push_back({ "mesh", "decimate" });
	
		isRemeshToggled = false;
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("Remake the model with new topology"); //CHANGE HERE
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}
/*
void SelectorToggleButton()
{
	int pushedColors = 0;
	if (isSelectorToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Select", ImVec2(buttonWidth3, buttonHeight)))
	{
		resetToggleButtons();
		isSelectorToggled = !isSelectorToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "select" });
	};
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}
*/
/*
void OctreeVisualizeToggleButton()
{
	int pushedColors = 0;

	if (isOctreeToggled)
	{
		toggleTrue();
		pushedColors += 4;
	}
	else
	{
		toggleFalse();
		pushedColors += 4;
	}
	if (ImGui::Button("Visualize Octree", ImVec2(buttonWidth2, buttonHeight)))
	{
		isOctreeToggled = !isOctreeToggled;
		MainDirectiveDefinition::Directives.push_back({ "octree", "visualize"});
	}
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
	{
		ImGui::SetTooltip("TBA"); //GHANGE HERE
	}
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}
*/
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

	ImGui::Text("Brushes");
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(857, 0.0f)); //Change here if more brushes are added
	ImGui::SameLine();
	ImGui::Text("Operations");

	StrokeToggleButton();
	BrushToggleButton();
	ExtrudeToggleButton();
	PullToggleButton();
	//StrokeSmoothToggleButton();
	SmoothToggleButton();
	ColorToggleButton();
	SmoothedColorToggleButton();
	NoiseToggleButton();
	InflateToggleButton();
	TessellationToggleButton();
	ImGui::Dummy(ImVec2(6, 0.0f)); 
	ImGui::SameLine();
	SimpleSubdivToggleButton();
	loopToggleButton();
	DecimationToggleButton();
	RemeshToggleButton();
	//SelectorToggleButton();
	//OctreeVisualizeToggleButton();

	ImGui::End();
}