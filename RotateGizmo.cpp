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
	if (position != cMesh.center)
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
					mouseStartPos = glm::normalize(mousePos - meshPos);
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

void RotateGizmoDefinition::RotateGizmo::draw()
{
	if (activeAxis != GizmoAxis::NONE)
	{
		rings[activeAxis]->mesh.uploadOffsetandScaleToGPU();
		rings[activeAxis]->mesh.renderWithStaticColor(rings[activeAxis]->activeColor);
	}
	else {
		forall(ring, rings)
		{
			ring->mesh.uploadOffsetandScaleToGPU();
			if (ring->hovered) {
				ring->mesh.renderWithStaticColor(ring->hoverColor);
			}
			else {
				ring->mesh.render();
			}
		}
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

	mousePos = glm::normalize(mousePos - meshPos);

	v4 lineColor;

	v3 x = mouseStartPos;
	v3 y = mousePos;

	float angle;
	switch (activeAxis)
	{
		case GizmoAxis::X: 
			lineColor = GizmoColors::red; 
			angle = atan2(x.y, x.z) - atan2(y.y, y.z);
			break;
		case GizmoAxis::Y: 
			lineColor = GizmoColors::green; 
			angle = atan2(x.z, x.x) - atan2(y.z, y.x);
			break;
		case GizmoAxis::Z: 
			lineColor = GizmoColors::blue; 
			angle = atan2(x.x, x.y) - atan2(y.x, y.y);
			break;
		default: say "No active axis..." done; return;
	}
	
	if (!didRotate)
	{
		didRotate = true;
	}
	else {
		float delta = angle - cMesh.eulerRotations[activeAxis];

		if (fabs(delta) > 0.001)
		{
			cMesh.setTranslation(v3(0,0,0));
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
			cMesh.setTranslation(meshPos);
		}
		Debug::Drawing::drawLine(meshPos, meshPos + mouseStartPos * ringScales[activeAxis], v4(1, 1, 1, 1));
	}

	cMesh.eulerRotations[activeAxis] = angle;
	Debug::Drawing::drawLine(meshPos, meshPos + mousePos * ringScales[activeAxis], lineColor);
}