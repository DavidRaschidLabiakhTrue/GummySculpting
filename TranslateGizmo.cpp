#include "TranslateGizmo.hpp"

TranslateGizmoDefinition::TranslateGizmo::TranslateGizmo()
{
}

TranslateGizmoDefinition::TranslateGizmo::~TranslateGizmo()
{
}

TranslateGizmoDefinition::TranslateGizmo::TranslateGizmo(bool trueConstructor)
{
	arrows[0] = CreateGizmoMesh(arrowFileName, GizmoColors::red, v3(-0.5f, 0.0f, 0.0f), 1.57f, GizmoAxes::z, 0.5f);	//X-axis
	arrows[1] = CreateGizmoMesh(arrowFileName, GizmoColors::green, v3(0.0f, 0.5f, 0.0f), 0.0f, GizmoAxes::y, 0.5f);	//Y-axis
	arrows[2] = CreateGizmoMesh(arrowFileName, GizmoColors::blue, v3(0.0f, 0.0f, 0.5f), 1.57f, GizmoAxes::x, 0.5f);	//Z-axis
}

bool TranslateGizmoDefinition::TranslateGizmo::query()
{
	if (!active and cast() and this->currentDir != direction)
	{
		return true;
	}
	else if (active and CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT)) {
		return false;
	}
	return false;
}

void TranslateGizmoDefinition::TranslateGizmo::draw()
{
	forall(arrow, arrows)
	{
		arrow.uploadOffsetandScaleToGPU();
		arrow.render();
	}
}