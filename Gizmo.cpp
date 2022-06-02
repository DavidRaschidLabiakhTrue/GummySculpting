#include "Gizmo.hpp"

#include "KeyInput.hpp"

using namespace GizmoDefinition;

GizmoDefinition::Gizmo::Gizmo()
{

}

GizmoDefinition::Gizmo::~Gizmo()
{

}

GizmoDefinition::Gizmo::Gizmo(bool trueConstructor)
{

}

void GizmoDefinition::Gizmo::queryGizmo()
{
	if (!gizmoActive && cast() and this->currentDir != direction)
	{
		gizmoActive = true;
		say "gizmo active" done;
	}
	else if (gizmoActive && CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT)) {
		gizmoActive = false;
		say "gizmo deactivated" done;
	}
}