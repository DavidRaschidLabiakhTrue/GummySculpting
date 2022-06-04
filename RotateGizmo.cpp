#include "RotateGizmo.hpp"

RotateGizmoDefinition::RotateGizmo::RotateGizmo()
{
}

RotateGizmoDefinition::RotateGizmo::~RotateGizmo()
{
}

RotateGizmoDefinition::RotateGizmo::RotateGizmo(bool trueConstructor)
{
	outerSphere = createGizmoMesh(sphereFileName, GizmoColors::darkGray, v3(0.0f, 0.0f, 0.0f), 0.0f, GizmoAxes::x, 0.2f, true);
	innerSphere = createGizmoMesh(sphereFileName, GizmoColors::lightGray, v3(0.0f, 0.0f, 0.0f), 0.0f, GizmoAxes::x, 0.19f);
}

void RotateGizmoDefinition::RotateGizmo::query(MeshReference cMesh)
{
	if (!active and cast() and this->currentDir != direction)
	{

	}
	else if (active) {

	}
}

void RotateGizmoDefinition::RotateGizmo::draw()
{
	outerSphere.uploadOffsetandScaleToGPU();
	outerSphere.render();

	innerSphere.uploadOffsetandScaleToGPU();
	innerSphere.render();
}

void RotateGizmoDefinition::RotateGizmo::RotateMesh(MeshReference cMesh, float radians, v3 axis)
{
	//TODO: Implement a function that Rotates the current mesh along the given axis based on the mouse movement
	return;
}