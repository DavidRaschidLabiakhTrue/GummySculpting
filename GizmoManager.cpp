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
	this->currentGizmo = new TranslateGizmo(TrueConstructor);
}

void GizmoManagerDefinition::GizmoManager::queryGizmo()
{
	currentGizmo->query();
}

void GizmoManagerDefinition::GizmoManager::drawGizmo()
{
	currentGizmo->draw();
}