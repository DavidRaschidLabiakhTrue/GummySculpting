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
	if (ImGui::Button("Stroke", ImVec2(buttonWidth1, buttonHeight)))
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
	if (ImGui::Button("Stroke Smoothing", ImVec2(buttonWidth2, buttonHeight)))
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
	if (ImGui::Button("Smooth", ImVec2(buttonWidth1, buttonHeight)))
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
	if (ImGui::Button("Color", ImVec2(buttonWidth1, buttonHeight)))
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
	if (ImGui::Button("Color Smoothing", ImVec2(buttonWidth2, buttonHeight)))
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
	if (ImGui::Button("Noise", ImVec2(buttonWidth1, buttonHeight)))
	{
		resetToggleButtons();
		isNoiseToggled = !isNoiseToggled;
		MainDirectiveDefinition::Directives.push_back({ "sculptor", "noise" });
	};
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
	};
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
	if (ImGui::Button("Simple Subdivide", ImVec2(buttonWidth2, buttonHeight)))
	{
		isSimpleSubToggled = true;
		MainDirectiveDefinition::Directives.push_back({ "mesh", "simplesubdivide", "1" });
		Sleep(buttonDelay);
		isSimpleSubToggled = false;
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
	if (ImGui::Button("Loop Subdivide", ImVec2(buttonWidth2, buttonHeight)))
	{
		isLoopToggled = true;
		MainDirectiveDefinition::Directives.push_back({ "mesh", "loopsubdivide", "1" });
		Sleep(buttonDelay);
		isLoopToggled = false;
	};
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
		Sleep(buttonDelay);
		isDecimateToggled = false;
	};
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
	if (ImGui::Button("Remesh", ImVec2(buttonWidth3, buttonHeight)))
	{
		isDecimateToggled = true;
		MainDirectiveDefinition::Directives.push_back({ "mesh", "remesh" });
		Sleep(buttonDelay);
		isRemeshToggled = false;
	};
	ImGui::PopStyleColor(pushedColors);
	ImGui::SameLine();
}

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

	ImGui::Text("Brushes");
	ImGui::SameLine();
	ImGui::Dummy(ImVec2(665, 0.0f)); //Change here if more brushes are added
	ImGui::SameLine();
	ImGui::Text("Operations");

	StrokeToggleButton();
	//StrokeSmoothToggleButton();
	SmoothToggleButton();
	ColorToggleButton();
	SmoothedColorToggleButton();
	NoiseToggleButton();
	InflateToggleButton();
	TessellationToggleButton();
	ImGui::Dummy(ImVec2(6, 0.0f)); //Change here if more brushes are added
	ImGui::SameLine();
	SimpleSubdivToggleButton();
	loopToggleButton();
	DecimationToggleButton();
	RemeshToggleButton();
	SelectorToggleButton();
	OctreeVisualizeToggleButton();

	ImGui::End();
}