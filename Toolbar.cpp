#include "Toolbar.hpp"

using namespace TopBarDefinition;

static float toolbarHeight = 45;
static float buttonHeight = 30;

static bool isStrokeToggled = false;
static bool isStrokeSmoothToggled = false;
static bool isSmoothToggled = false;
static bool isColorToggled = false;
static bool isSmoothedColorToggled = false;
static bool isNoiseToggled = false;
static bool isSimpleSubToggled = false;
static bool isLoopToggled = false;
static bool isTessellationToggled = false;
static bool isDecimateToggled = false;

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
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(200, 50, 250)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(200, 150, 200))); // should probably change these colors, bright blue hard to see.
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0)));
}

void toggleFalse()
{
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255)));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(20, 200, 200)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(200, 150, 200)));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0)));
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
	if (ImGui::Button("Stroke Brush", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
;		isStrokeToggled = !isStrokeToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "dirac" });
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
	if (ImGui::Button("Stroke Smooth Brush", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
		isStrokeSmoothToggled = !isStrokeSmoothToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "stroke" });
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
	if (ImGui::Button("Smooth Brush", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
		isSmoothToggled = !isSmoothToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "smooth" });
	};
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
	if (ImGui::Button("Color Brush", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
		isColorToggled = !isColorToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "color" });
	};
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
	if (ImGui::Button("Smoothed Color Brush", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
		isSmoothedColorToggled = !isSmoothedColorToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "smoothedcolor" });
	};
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
	if (ImGui::Button("Noise Brush", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
		isNoiseToggled = !isNoiseToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "noise" });
	};
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
	if (ImGui::Button("Simple Subdivide", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
		isSimpleSubToggled = !isSimpleSubToggled;
		MainDirectiveDefinition::Directives.push_back({ "mesh", "simplesubdivide", "1" });
	};
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
	if (ImGui::Button("Loop Subdivide", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
		isLoopToggled = !isLoopToggled;
		MainDirectiveDefinition::Directives.push_back({ "mesh", "loopsubdivide", "1" });
	};
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}
void TessellationToggleButton()
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
	if (ImGui::Button("Tessellation", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
		isTessellationToggled = !isTessellationToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "tessellate" });
	};
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

void DecimationToggleButton()
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
	if (ImGui::Button("Decimation", ImVec2(0, buttonHeight)))
	{
		resetToggleButtons();
		isDecimateToggled = !isDecimateToggled;
		MainDirectiveDefinition::Directives.push_back({ "mesh", "decimate" });
	};
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
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

	StrokeToggleButton();
	//StrokeSmoothToggleButton();
	SmoothToggleButton();
	ColorToggleButton();
	SmoothedColorToggleButton();
	NoiseToggleButton();
	SimpleSubdivToggleButton();
	loopToggleButton();
	TessellationToggleButton();
	DecimationToggleButton();

	ImGui::End();
}