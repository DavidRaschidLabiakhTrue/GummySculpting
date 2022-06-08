#include "RotateGizmo.hpp"

RotateGizmoDefinition::RotateGizmo::RotateGizmo()
{
}

RotateGizmoDefinition::RotateGizmo::~RotateGizmo()
{
}

RotateGizmoDefinition::RotateGizmo::RotateGizmo(bool trueConstructor)
{
	//X-axis
	shared_ptr<Ring> xRing = make_shared<Ring>(GizmoAxis::X, GizmoColors::red, GizmoColors::lightRed,
		GizmoColors::lightOrange, 1.57, v3(0, 1, 0), ringScales[0]);
	rings.push_back(xRing);
	handles.push_back(dynamic_pointer_cast<Handle>(xRing));

	//Y-axis
	shared_ptr<Ring> yRing = make_shared<Ring>(GizmoAxis::Y, GizmoColors::green, GizmoColors::lightGreen,
		GizmoColors::lightOrange, 1.57, v3(1, 0, 0), ringScales[1]);
	rings.push_back(yRing);
	handles.push_back(dynamic_pointer_cast<Handle>(yRing));

	//Z-axis
	shared_ptr<Ring> zRing = make_shared<Ring>(GizmoAxis::Z, GizmoColors::blue, GizmoColors::lightBlue,
		GizmoColors::lightOrange, 1.57, v3(0, 0, 1), ringScales[2]);
	rings.push_back(zRing);
	handles.push_back(dynamic_pointer_cast<Handle>(zRing));

	activeAxis = GizmoAxis::NONE;
}

RotateGizmoDefinition::RotateGizmo::Ring::Ring(GizmoAxis axis, v4 color, v4 hoverColor, v4 activeColor, float rot, v3 rotAxis, float scale) : Handle(TrueConstructor)
{
	this->mesh = createGizmoMesh(ringFileName, color, v3(0,0,0), rot, rotAxis, scale);
	this->offsetFromGizmo = v3(0, 0, 0);
	this->axis = axis;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

void RotateGizmoDefinition::RotateGizmo::query(MeshReference cMesh)
{
	if (state.meshID != cMesh.meshID) {
		state = RotateGizmoState(cMesh.meshID, cMesh.eulerRotations, cMesh.center); //TODO: store rotations in mesh and get those here
	}

	if (position != state.position)
	{
		moveGizmo(cMesh.center);
	}

	checkClicked();

	if (activeAxis == GizmoAxis::NONE)
	{
		if (didRotate)
		{
			didRotate = false;
		}
		v3 camPos = this->origin().position;
		v3 meshPos = state.position;

		forall(ring, rings)
		{
			v3 planeNormal = getPlaneNormal(ring->axis);
			v3 mousePos = getRayPlaneIntersect(meshPos, planeNormal, camPos, this->direction);
			float radius = glm::distance(meshPos, mousePos);
			float distanceFromRing = glm::distance(meshPos, mousePos) - ring->mesh.scale;
			if (distanceFromRing < detectionRange //check if mouse is too far away
				and distanceFromRing > -1 * detectionRange //check if mouse is too close to center
				and glm::dot(mousePos - meshPos, this->direction) < detectionRange) //check for mouse on opposite side
			{
				if (clicked)
				{
					activeAxis = ring->axis;
					mouseStartPos = mousePos;
				}
				else {
					clearHover();
					ring->hovered = true;
				}
				return;
			}
			else {
				ring->hovered = false;
			}
		}
	}
	else
	{
		RotateMesh(cMesh);
	}
}

v3 RotateGizmoDefinition::RotateGizmo::getPlaneNormal(GizmoAxis axis)
{
	switch (axis)
	{
		case GizmoAxis::X: return v3(1, 0, 0);
		case GizmoAxis::Y: return v3(0, 1, 0);
		case GizmoAxis::Z: return v3(0, 0, 1);
		default: return v3(0, 0, 0);
	}
}

void RotateGizmoDefinition::RotateGizmo::RotateMesh(MeshReference cMesh)
{
	v3 camPos = this->origin().position;
	v3 meshPos = state.position;

	v3 planeNormal = getPlaneNormal(activeAxis);

	v3 mousePos = getRayPlaneIntersect(meshPos, planeNormal, camPos, this->direction);
	v4 lineColor;
	v3 referenceAngle;

	switch (activeAxis)
	{
		case GizmoAxis::X: 
			lineColor = GizmoColors::red; 
			referenceAngle = v3(0, 1, 0);
			break;
		case GizmoAxis::Y: 
			lineColor = GizmoColors::green; 
			referenceAngle = v3(0, 0, -1);
			break;
		case GizmoAxis::Z: 
			lineColor = GizmoColors::blue; 
			referenceAngle = v3(0, 1, 0);
			break;
		default: say "No active axis..." done; return;
	}
	
	float mouseStartAngle = glm::angle(referenceAngle, glm::normalize(mouseStartPos));

	float newMouseAngle = glm::angle(referenceAngle, glm::normalize(mousePos));

	float trueAngle = newMouseAngle - mouseStartAngle;

	float delta;
	if (!didRotate)
	{
		didRotate = true;
		delta = trueAngle;
	}
	else {
		delta = trueAngle - state.rotations[activeAxis];
	}

	if (fabs(delta) > 0.001)
	{
		switch (activeAxis)
		{
		case GizmoAxis::X:
			cMesh.rotateX(delta);
			break;
		case GizmoAxis::Y:
			cMesh.rotateY(delta);
			break;
		case GizmoAxis::Z:
			cMesh.rotateZ(delta);
			break;
		}
	}

	state.rotations[activeAxis] = trueAngle;

	Debug::Drawing::drawLine(meshPos, mouseStartPos, v4(1, 1, 1, 1));
	Debug::Drawing::drawLine(meshPos, glm::normalize(mousePos) * ringScales[activeAxis], lineColor);
}