#include "GizmoManager.hpp"

using namespace GizmoManagerDefinition;

GizmoManagerDefinition::GizmoManager::GizmoManager()
{

}

GizmoManagerDefinition::GizmoManager::~GizmoManager()
{

}

GizmoManagerDefinition::GizmoManager::GizmoManager(bool trueConstructor)
{
	this->translateGizmo = new TranslateGizmo(TrueConstructor);
	this->rotateGizmo = new RotateGizmo(TrueConstructor);
}

void GizmoManagerDefinition::GizmoManager::setCurrentGizmo()
{
	switch (state)
	{
		case NONE: break;
		case TRANSLATE: currentGizmo = translateGizmo; break;
		case ROTATE: currentGizmo = rotateGizmo; break;
	}
}

void GizmoManagerDefinition::GizmoManager::iterateState()
{
	switch (state)
	{
		case NONE: state = TRANSLATE; break;
		case TRANSLATE: state = ROTATE; break;
		case ROTATE: state = NONE; break;
	}
	setCurrentGizmo();
}

void GizmoManagerDefinition::GizmoManager::queryGizmo(MeshReference cMesh)
{
	if (KeyInputDefinition::isPressed(GLFW_KEY_Q))
	{
		iterateState();
	}

	if (CheckMouseHeld(GLFW_MOUSE_BUTTON_MIDDLE))
	{
		say "held" done;
	}

	if (state != NONE)
	{
		currentGizmo->query(cMesh);
	}
}

void GizmoManagerDefinition::GizmoManager::drawGizmo()
{
	if (state != NONE)
	{
		currentGizmo->draw();
	}
}