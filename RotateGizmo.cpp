#include "RotateGizmo.hpp"

RotateGizmoDefinition::RotateGizmo::RotateGizmo()
{
}

RotateGizmoDefinition::RotateGizmo::~RotateGizmo()
{
}

RotateGizmoDefinition::RotateGizmo::RotateGizmo(bool trueConstructor)
{
	outerSphere = createGizmoMesh(sphereFileName, GizmoColors::darkGray, v3(0.0f, 0.0f, 0.0f), 0.0f, GizmoAxes::x, 0.2f);
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
	glEnable(GL_DEPTH_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	innerSphere.uploadOffsetandScaleToGPU();
	innerSphere.render();

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);


	outerSphere.uploadOffsetandScaleToGPU();
	outerSphere.render();


	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glEnable(GL_DEPTH_TEST);

	/*
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	innerSphere.uploadOffsetandScaleToGPU();
	innerSphere.renderWithStaticColor(v4(1.0, 0.0, 0.0, 0.1));

	glDisable(GL_BLEND);

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);

	outerSphere.uploadOffsetandScaleToGPU();
	outerSphere.renderWithStaticColor(GizmoColors::lightGray);

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glEnable(GL_DEPTH_TEST);
	*/
}

void RotateGizmoDefinition::RotateGizmo::RotateMesh(MeshReference cMesh, float radians, v3 axis)
{
	//TODO: Implement a function that Rotates the current mesh along the given axis based on the mouse movement
	return;
}