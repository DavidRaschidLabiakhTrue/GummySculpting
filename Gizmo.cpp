#include "Gizmo.hpp"

using namespace GizmoDefinition;

Gizmo::Gizmo()
{

}

Gizmo::~Gizmo()
{

}

Gizmo::Handle::Handle(string fileName, v4 color, v4 hoverColor, v3 offset, float scale, float rot, v3 rotAxis, GizmoAxis axis)
{
	this->mesh = StaticMesh();
	this->mesh.initialize(this->mesh, fileName, color, offset, scale, rot, rotAxis);
	this->axis = axis;
	this->hoverColor = hoverColor;
	this->offsetFromGizmo = offset;
}

Gizmo::Gizmo(bool trueConstructor)
{
	//init arrows
	arrows.push_back(Handle(
		arrowFileName, GizmoColors::red, GizmoColors::lightRed, v3(-0.5, 0, 0), arrowScale, 1.57f, v3(0, 0, 1), GizmoAxis::X)
	);
	arrows.push_back(Handle(
		arrowFileName, GizmoColors::green, GizmoColors::lightGreen, v3(0, 0.5, 0), arrowScale, 0, v3(0, 1, 0), GizmoAxis::Y)
	);
	arrows.push_back(Handle(
		arrowFileName, GizmoColors::blue, GizmoColors::lightBlue, v3(0, 0, 0.5), arrowScale, 1.57f, v3(1, 0, 0), GizmoAxis::Z)
	);

	//init rings
	rings.push_back(Handle(
		ringFileName, GizmoColors::red, GizmoColors::lightRed, v3(0, 0, 0), ringScale, 1.57f, v3(0, 1, 0), GizmoAxis::X)
	);
	rings.push_back(Handle(
		ringFileName, GizmoColors::green, GizmoColors::lightGreen, v3(0, 0, 0), ringScale*0.99f, 1.57f, v3(1, 0, 0), GizmoAxis::Y)
	);
	rings.push_back(Handle(
		ringFileName, GizmoColors::blue, GizmoColors::lightBlue, v3(0, 0, 0), ringScale * 0.98f, 1.57f, v3(0, 0, 1), GizmoAxis::Z)
	);

	//init arms
	arms.push_back(Handle(
		armFileName, GizmoColors::red, GizmoColors::lightRed, v3(-0.5, 0, 0), armScale, 1.57f, v3(0, 0, 1), GizmoAxis::X)
	);
	arms.push_back(Handle(
		armFileName, GizmoColors::green, GizmoColors::lightGreen, v3(0, 0.5, 0), armScale, 1.57f, v3(0, 1, 0), GizmoAxis::Y)
	);
	arms.push_back(Handle(
		armFileName, GizmoColors::blue, GizmoColors::lightBlue, v3(0, 0, 0.5), armScale, 1.57f, v3(1, 0, 0), GizmoAxis::Z)
	);
	arms.push_back(Handle(
		cubeFileName, GizmoColors::yellow, GizmoColors::lightYellow, v3(0, 0, 0), cubeScale, 0, v3(0, 1, 0), GizmoAxis::ALL)
	);
}

void Gizmo::setState(GizmoState newState)
{
	state = newState;
	didChangeState = true;
}

void Gizmo::iterateState()
{
	switch (state)
	{
		case INACTIVE: setState(TRANSLATE); break;
		case TRANSLATE: setState(ROTATE); break;
		case ROTATE: setState(SCALE); break;
		case SCALE: setState(INACTIVE); break;
	}
}

void Gizmo::queryGizmo(MeshReference cMesh)
{
	if (KeyInputDefinition::isPressed(GLFW_KEY_Q))
	{
		iterateState();
	}
	if (KeyInputDefinition::isPressed(GLFW_KEY_R))
	{
		cMesh.resetModelMatrix();
		cMesh.rotationMatrix = m4(1);
		cMesh.translationValues = v3(0, 0, 0);
		cMesh.scaleValues = v3(1, 1, 1);
	}

	if (didChangeState)
	{
		didChangeState = false;
		moveGizmo(cMesh.translationValues);
	}

	switch (state)
	{
		case INACTIVE:
			break;
		case TRANSLATE:
			queryTranslate(cMesh);
			break;
		case ROTATE:
			queryRotate(cMesh);
			break;
		case SCALE:
			queryScale(cMesh);
			break;
	}
}

void Gizmo::drawGizmo()
{
	switch (state)
	{
		case INACTIVE:
			break;
		case TRANSLATE:
			drawTranslate();
			break;
		case ROTATE:
			drawRotate();
			break;
		case SCALE:
			drawScale();
			break;
	}
}

void Gizmo::moveHandles(v3 newPosition, vector<Handle>& handles)
{
	forall(handle, handles)
	{
		handle.mesh.offset = newPosition + handle.offsetFromGizmo;
	}
}

void Gizmo::moveGizmo(v3 newPosition)
{
	switch (state)
	{
		case INACTIVE:
			break;
		case TRANSLATE:
			moveHandles(newPosition, arrows);
			break;
		case ROTATE:
			moveHandles(newPosition, rings);
			break;
		case SCALE:
			moveHandles(newPosition, arms);
			break;
	}
}

bool Gizmo::sortHandlesByDistance(Handle const& lhs, Handle const& rhs) {
	return lhs.distanceFromCam < rhs.distanceFromCam;
}

void Gizmo::clearHover(vector<Handle>& handles)
{
	forall(handle, handles)
	{
		handle.hovered = false;
	}
}

float Gizmo::calculateMouseOffset(MeshReference cMesh)
{
	v3 center = cMesh.center;
	v3 camPosition = this->origin().position;
	v3 axis;
	v3 planeNormal;
	v3 normalXY = v3(0, 0, 1);
	v3 normalXZ = v3(0, 1, 0);
	v3 normalYZ = v3(1, 0, 0);
	switch (activeAxis)
	{
		case GizmoAxis::X:
			axis = v3(1, 0, 0);
			planeNormal = getFartherPlaneNormal(camPosition, center, normalXY, normalXZ);
			break;
		case GizmoAxis::Y:
			axis = v3(0, 1, 0);
			planeNormal = getFartherPlaneNormal(camPosition, center, normalXY, normalYZ);
			break;
		case GizmoAxis::Z:
			axis = v3(0, 0, 1);
			planeNormal = getFartherPlaneNormal(camPosition, center, normalXZ, normalYZ);
			break;
		default:
			return 0;
			break;
	}
	v3 planeIntersect = getRayPlaneIntersect(center, planeNormal, camPosition, this->direction);
	return glm::dot(planeIntersect, axis);
}

v3 Gizmo::getFartherPlaneNormal(v3 position, v3 center, v3 normalA, v3 normalB)
{
	float distanceA = distanceFromPointToPlane(position, center, normalA);
	float distanceB = distanceFromPointToPlane(position, center, normalB);
	if (distanceA > distanceB)
	{
		return normalA;
	}
	else {
		return normalB;
	}
}

//Translate
void Gizmo::queryTranslate(MeshReference cMesh)
{
	bool clicked = cast();
	if (!clicked)
	{
		screenToWorld();
		activeAxis = GizmoAxis::NONE;
	}

	if (activeAxis == GizmoAxis::NONE)
	{
		v3 camPos = this->origin().position;
		sort(arrows.begin(), arrows.end(), &sortHandlesByDistance);
		forall(arrow, arrows)
		{
			v3 center = arrow.mesh.getTrueCenter();
			arrow.distanceFromCam = glm::distance(camPos, center);
			v3 mousePos = camPos + (this->direction * arrow.distanceFromCam);
			float distFromGizmo = glm::distance(mousePos, center);

			if (clicked and distFromGizmo < 0.2)
			{
				clearHover(arrows);
				activeAxis = arrow.axis;
				prevMouseOffset = calculateMouseOffset(cMesh);
				return;
			}
			else {
				if (distFromGizmo < 0.2)
				{
					if (!arrow.hovered)
					{
						clearHover(arrows);
						arrow.hovered = true;
					}
					return;
				}
				else {
					arrow.hovered = false;
				}
			}
		}
	} else
	{
		translateMesh(cMesh);
	}
}

void Gizmo::drawTranslate()
{
	if (activeAxis != GizmoAxis::NONE)
	{
		forall(arrow, arrows)
		{
			if (arrow.axis == activeAxis)
			{
				arrow.mesh.uploadOffsetandScaleToGPU();
				arrow.mesh.renderWithStaticColor(GizmoColors::lightOrange);
			}
		}
	}
	else {
		forall(arrow, arrows)
		{
			arrow.mesh.uploadOffsetandScaleToGPU();
			if (arrow.hovered) {
				arrow.mesh.renderWithStaticColor(arrow.hoverColor);
			}
			else {
				arrow.mesh.render();
			}
		}
	}
}

void Gizmo::translateMesh(MeshReference cMesh)
{
	float newMouseOffset = calculateMouseOffset(cMesh);
	float delta = newMouseOffset - prevMouseOffset;

	if (delta != 0)
	{
		cMesh.translationValues[activeAxis] += delta;
		//cMesh.setTranslation(cMesh.translationValues);
		cMesh.applyAllTransforms();
		prevMouseOffset = newMouseOffset;
		moveHandles(cMesh.translationValues, arrows);
	}
}

//Rotate
void Gizmo::queryRotate(MeshReference cMesh)
{
	bool clicked = cast();
	if (!clicked)
	{
		screenToWorld();
		activeAxis = GizmoAxis::NONE;
	}

	if (activeAxis == GizmoAxis::NONE)
	{
		v3 camPos = this->origin().position;
		v3 meshPos = cMesh.translationValues;

		forall(ring, rings)
		{
			v3 planeNormal;
			switch (ring.axis)
			{
				case GizmoAxis::X: planeNormal = v3(1, 0, 0); break;
				case GizmoAxis::Y: planeNormal = v3(0, 1, 0); break;
				case GizmoAxis::Z: planeNormal = v3(0, 0, 1); break;
				default: return;
			}
			v3 mousePos = getRayPlaneIntersect(meshPos, planeNormal, camPos, this->direction);
			float radius = glm::distance(meshPos, mousePos);
			float distanceFromRing = glm::distance(meshPos, mousePos) - ring.mesh.scale;
			if (distanceFromRing < 0.1f //check if mouse is too far away
				and distanceFromRing > -1 * 0.1f //check if mouse is too close to center
				and glm::dot(mousePos - meshPos, this->direction) < 0.1f) //check for mouse on opposite side
			{
				if (clicked)
				{
					activeAxis = ring.axis;
					startMousePosition = prevMousePosition = glm::normalize(mousePos - meshPos);
				}
				else {
					clearHover(arrows);
					ring.hovered = true;
				}
				return;
			}
			else {
				ring.hovered = false;
			}
		}
	}
	else
	{
		rotateMesh(cMesh);
	}
}

void Gizmo::drawRotate()
{
	if (activeAxis != GizmoAxis::NONE)
	{
		forall(ring, rings)
		{
			if (ring.axis == activeAxis)
			{
				ring.mesh.uploadOffsetandScaleToGPU();
				ring.mesh.renderWithStaticColor(GizmoColors::lightOrange);
			}
		}
	}
	else {
		forall(ring, rings)
		{
			ring.mesh.uploadOffsetandScaleToGPU();
			if (ring.hovered) {
				ring.mesh.renderWithStaticColor(ring.hoverColor);
			}
			else {
				ring.mesh.render();
			}
		}
	}
}

void Gizmo::rotateMesh(MeshReference cMesh)
{
	v3 camPos = this->origin().position;
	v3 meshPos = cMesh.translationValues;

	v3 planeNormal;
	switch (activeAxis)
	{
		case GizmoAxis::X: 
			planeNormal = v3(1, 0, 0); 
			break;
		case GizmoAxis::Y: 
			planeNormal = v3(0, 1, 0); 
			break;
		case GizmoAxis::Z: 
			planeNormal = v3(0, 0, 1); 
			break;
		default: 
			return;
	}

	v3 newMousePosition = getRayPlaneIntersect(meshPos, planeNormal, camPos, this->direction);

	newMousePosition = glm::normalize(newMousePosition - meshPos);

	v4 lineColor;

	v3 x = prevMousePosition;
	v3 y = newMousePosition;

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
		default: 
			return;
	}

	cMesh.rotationMatrix = glm::rotate(angle, planeNormal) * cMesh.rotationMatrix;
	cMesh.setTranslation(v3(0));
	cMesh.applyAllTransforms();
	prevMousePosition = newMousePosition;

	Debug::Drawing::drawLine(meshPos, meshPos + startMousePosition * ringScale * 0.95f, v4(1, 1, 1, 1));
	Debug::Drawing::drawLine(meshPos, meshPos + newMousePosition * ringScale * 0.95f, lineColor);
}

//Scale
void Gizmo::queryScale(MeshReference cMesh)
{
	bool clicked = cast();
	if (!clicked)
	{
		screenToWorld();
		activeAxis = GizmoAxis::NONE;
	}

	if (activeAxis == GizmoAxis::NONE)
	{
		v3 camPos = this->origin().position;
		sort(arms.begin(), arms.end(), &sortHandlesByDistance);
		forall(arm, arms)
		{
			v3 center = arm.mesh.getTrueCenter();
			arm.distanceFromCam = glm::distance(camPos, center);
			v3 mousePos = camPos + (this->direction * arm.distanceFromCam);
			float distFromGizmo = glm::distance(mousePos, center);

			if (clicked and distFromGizmo < 0.2)
			{
				clearHover(arms);
				activeAxis = arm.axis;
				if (activeAxis == GizmoAxis::ALL)
				{
					prevMouseDistance = distFromGizmo;
					startMousePosition = glm::normalize(mousePos - center);
				}
				else {
					prevMouseOffset = calculateMouseOffset(cMesh);
				}
				return;
			}
			else {
				if (distFromGizmo < 0.2)
				{
					if (!arm.hovered)
					{
						clearHover(arms);
						arm.hovered = true;
					}
					return;
				}
				else {
					arm.hovered = false;
				}
			}
		}
	}
	else
	{
		scaleMesh(cMesh);
	}
}

void Gizmo::drawScale()
{
	if (activeAxis != GizmoAxis::NONE)
	{
		forall(arm, arms)
		{
			if (arm.axis == activeAxis)
			{
				arm.mesh.uploadOffsetandScaleToGPU();
				arm.mesh.renderWithStaticColor(GizmoColors::lightOrange);
			}
		}
	}
	else {
		forall(arm, arms)
		{
			arm.mesh.uploadOffsetandScaleToGPU();
			if (arm.hovered) {
				arm.mesh.renderWithStaticColor(arm.hoverColor);
			}
			else {
				arm.mesh.render();
			}
		}
	}
}

void Gizmo::scaleMesh(MeshReference cMesh)
{
	if (activeAxis == GizmoAxis::ALL)
	{
		v3 camPos = this->origin().position;
		v3 meshPos = cMesh.translationValues;
		v3 newMousePos = camPos + (this->direction * glm::distance(camPos, meshPos));
		float newMouseDistance = glm::distance(newMousePos, meshPos);
		float delta = newMouseDistance - prevMouseDistance;
		if (delta != 0)
		{
			float scaleValue;
			float dot = glm::dot(startMousePosition, glm::normalize(newMousePos - meshPos));
			if (dot > 0)
			{
				scaleValue = 1 + delta;
			}
			else {
				scaleValue = 1 - delta;
			}
			cMesh.scaleValues *= scaleValue;
			cMesh.applyAllTransforms();
			prevMouseDistance = newMouseDistance;
		}
	}
	else 
	{
		float newMouseOffset = calculateMouseOffset(cMesh);

		float delta = newMouseOffset - prevMouseOffset;
		if (delta != 0)
		{
			float scaleValue;
			switch (activeAxis)
			{
				case GizmoAxis::X:
					scaleValue = 1 - delta;
					cMesh.scaleValues.x *= scaleValue;
					break;
				case GizmoAxis::Y:
					scaleValue = 1 + delta;
					cMesh.scaleValues.y *= scaleValue;
					break;
				case GizmoAxis::Z:
					scaleValue = 1 + delta;
					cMesh.scaleValues.z *= scaleValue;
					break;
				default: break;
			}
			cMesh.applyAllTransforms();
			prevMouseOffset = newMouseOffset;
		}
	}
}