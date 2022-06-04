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

void GizmoManagerDefinition::GizmoManager::queryGizmo(MeshReference cMesh)
{
	currentGizmo->query(cMesh);
}

void GizmoManagerDefinition::GizmoManager::drawGizmo()
{
	currentGizmo->draw();
}