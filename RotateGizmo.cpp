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
		GizmoColors::lightOrange, 1.57, v3(0, 0, 1), 0.3);
	rings.push_back(xRing);
	handles.push_back(dynamic_pointer_cast<Handle>(xRing));

	//Y-axis
	shared_ptr<Ring> yRing = make_shared<Ring>(GizmoAxis::Y, GizmoColors::green, GizmoColors::lightGreen,
		GizmoColors::lightOrange, 1.57, v3(0, 1, 0), 0.297);
	rings.push_back(yRing);
	handles.push_back(dynamic_pointer_cast<Handle>(yRing));

	//Z-axis
	shared_ptr<Ring> zRing = make_shared<Ring>(GizmoAxis::Z, GizmoColors::blue, GizmoColors::lightBlue,
		GizmoColors::lightOrange, 1.57, v3(1, 0, 0), 0.295);
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
		state = RotateGizmoState(cMesh.meshID, cMesh.center);
	}

	checkClicked();

	if (!active)
	{
		v3 camPos = this->origin().position;
		v3 meshPos = cMesh.center;

		forall(ring, rings)
		{
			v3 planeNormal;
			switch (ring->axis)
			{
				case GizmoAxis::X: planeNormal = v3(0, 0, 1); break;
				case GizmoAxis::Y: planeNormal = v3(1, 0, 0); break;
				case GizmoAxis::Z: planeNormal = v3(0, 1, 0); break;
				default: planeNormal = v3(0, 0, 0); break;
			}
			v3 mousePos = getRayPlaneIntersect(meshPos, planeNormal, camPos, this->direction);
			float radius = glm::distance(meshPos, mousePos);
			//Debug::Drawing::drawLine(meshPos, mousePos, v4(1, 0, 0, 1));
			float distanceFromRing = glm::distance(meshPos, mousePos) - ring->mesh.scale;
			if (distanceFromRing < detectionRange //check if mouse is too far away
				and distanceFromRing > -1 * detectionRange //check if mouse is too close to center
				and glm::dot(mousePos - meshPos, this->direction) < detectionRange) //check for mouse on opposite side
			{
				clearHover();
				ring->hovered = true;
				return;
			}
			else {
				ring->hovered = false;
			}
		}
	}
}

void RotateGizmoDefinition::RotateGizmo::RotateMesh(MeshReference cMesh, float radians, v3 axis)
{
	//TODO: Implement a function that Rotates the current mesh along the given axis based on the mouse movement
	return;
}