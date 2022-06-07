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
		GizmoColors::lightOrange, 1.57, v3(0, 1, 0), ringScale);
	rings.push_back(xRing);
	handles.push_back(dynamic_pointer_cast<Handle>(xRing));

	//Y-axis
	shared_ptr<Ring> yRing = make_shared<Ring>(GizmoAxis::Y, GizmoColors::green, GizmoColors::lightGreen,
		GizmoColors::lightOrange, 1.57, v3(1, 0, 0), ringScale * 0.99);
	rings.push_back(yRing);
	handles.push_back(dynamic_pointer_cast<Handle>(yRing));

	//Z-axis
	shared_ptr<Ring> zRing = make_shared<Ring>(GizmoAxis::Z, GizmoColors::blue, GizmoColors::lightBlue,
		GizmoColors::lightOrange, 1.57, v3(0, 0, 1), ringScale * 0.98);
	rings.push_back(zRing);
	handles.push_back(dynamic_pointer_cast<Handle>(zRing));

	activeAxis = GizmoAxis::NONE;
}

RotateGizmoDefinition::RotateGizmo::Ring::Ring(GizmoAxis axis, v4 color, v4 hoverColor, v4 activeColor, float rot, v3 rotAxis, float scale) : Handle(TrueConstructor)
{
	this->mesh = createGizmoMesh(ringFileName, color, v3(0,0,0), rot, rotAxis, scale);
	this->axis = axis;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

void RotateGizmoDefinition::RotateGizmo::query(MeshReference cMesh)
{
	if (state.meshID != cMesh.meshID) {
		state = RotateGizmoState(cMesh.meshID, v3(0,0,0)); //TODO: store rotations in mesh and get those here
		didRotate = false;
	}
	else if (didRotate)
	{

	}

	checkClicked();

	if (activeAxis == GizmoAxis::NONE)
	{
		v3 camPos = this->origin().position;
		v3 meshPos = cMesh.center;

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
	v3 meshPos = cMesh.center;

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

	float angleDelta = newMouseAngle - mouseStartAngle;

	switch (activeAxis)
	{
		case GizmoAxis::X:
			cMesh.rotateX(angleDelta - newRotation[activeAxis]);
			break;
		case GizmoAxis::Y:
			cMesh.rotateY(angleDelta - newRotation[activeAxis]);
			break;
		case GizmoAxis::Z:
			cMesh.rotateZ(angleDelta - newRotation[activeAxis]);
			break;
		default: return;
	}

	newRotation[activeAxis] = angleDelta;

	didRotate = true;

	Debug::Drawing::drawLine(meshPos, mouseStartPos, v4(1, 1, 1, 1));
	Debug::Drawing::drawLine(meshPos, glm::normalize(mousePos) * ringScale, lineColor);
}