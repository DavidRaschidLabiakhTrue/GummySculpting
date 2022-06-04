#include "TranslateGizmo.hpp"

TranslateGizmoDefinition::TranslateGizmo::TranslateGizmo()
{
}

TranslateGizmoDefinition::TranslateGizmo::~TranslateGizmo()
{
}

TranslateGizmoDefinition::TranslateGizmo::TranslateGizmo(bool trueConstructor)
{
	arrows[0].mesh = createGizmoMesh(arrowFileName, GizmoColors::red, v3(-0.5f, 0.0f, 0.0f), 1.57f, GizmoAxes::z, 0.5f);	//X-axis
	arrows[0].callback = [&](MeshReference cMesh) -> void { translateMesh(cMesh, GizmoAxes::x); };

	arrows[1].mesh = createGizmoMesh(arrowFileName, GizmoColors::green, v3(0.0f, 0.5f, 0.0f), 0.0f, GizmoAxes::y, 0.5f);	//Y-axis
	arrows[1].callback = [&](MeshReference cMesh) -> void { translateMesh(cMesh, GizmoAxes::y); };

	arrows[2].mesh = createGizmoMesh(arrowFileName, GizmoColors::blue, v3(0.0f, 0.0f, 0.5f), 1.57f, GizmoAxes::x, 0.5f);	//Z-axis
	arrows[2].callback = [&](MeshReference cMesh) -> void { translateMesh(cMesh, GizmoAxes::z); };
}

void TranslateGizmoDefinition::TranslateGizmo::query(MeshReference cMesh)
{
	if (!active and cast() and this->currentDir != direction)
	{
		for (int i = 0; i < numArrows; i++)
		{
			if (detectMeshClick(arrows[i].mesh))
			{
				activeArrowIndex = i;
				active = true;
				return;
			}
		}
	}
	else if (active and activeArrowIndex != -1) {
		if (CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT)) {
			active = false;
			activeArrowIndex = -1;
		}
		else {
			arrows[activeArrowIndex].callback(cMesh);
		}
	}
}

void TranslateGizmoDefinition::TranslateGizmo::draw()
{
	for (int i = 0; i < numArrows; i++)
	{
		arrows[i].mesh.uploadOffsetandScaleToGPU();
		if (i == activeArrowIndex)
		{
			arrows[i].mesh.renderWithStaticColor(GizmoColors::lightOrange);
		}
		else {
			arrows[i].mesh.render();
		}
	}
}

void TranslateGizmoDefinition::TranslateGizmo::translateMesh(MeshReference cMesh, v3 axis)
{
	//TODO: Implement a function that translates the current mesh along the given axis based on the mouse movement
	return;
}