#include "TranslateGizmo.hpp"

using namespace MathTypeDefinitions;
using namespace TranslateGizmoDefinition;

TranslateGizmoDefinition::TranslateGizmo::TranslateGizmo() {}

TranslateGizmoDefinition::TranslateGizmo::~TranslateGizmo() {}

TranslateGizmoDefinition::TranslateGizmo::Arrow::Arrow(GizmoAxis axis, v4 color, v4 hoverColor, v4 activeColor, v3 offset, float rot, v3 rotAxis) : Handle(TrueConstructor)
{
	this->offsetFromGizmo = offset;
	this->mesh = createGizmoMesh(arrowFileName, color, offset, rot, rotAxis, arrowScale);
	this->axis = axis;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

TranslateGizmoDefinition::TranslateGizmo::TranslateGizmo(bool trueConstructor)
{
	//X-axis
	shared_ptr<Arrow> xArrow = make_shared<Arrow>(GizmoAxis::X, GizmoColors::red, GizmoColors::lightRed, 
		GizmoColors::lightOrange, v3(-0.5, 0, 0), 1.57, v3(0, 0, 1));
	arrows.push_back(xArrow);
	handles.push_back(dynamic_pointer_cast<Handle>(xArrow));

	//Y-axis
	shared_ptr<Arrow> yArrow = make_shared<Arrow>(GizmoAxis::Y, GizmoColors::green, GizmoColors::lightGreen,
		GizmoColors::lightOrange, v3(0, 0.5, 0), 0, v3(0, 1, 0));
	arrows.push_back(yArrow);
	handles.push_back(dynamic_pointer_cast<Handle>(yArrow));

	//Z-axis
	shared_ptr<Arrow> zArrow = make_shared<Arrow>(GizmoAxis::Z, GizmoColors::blue, GizmoColors::lightBlue,
		GizmoColors::lightOrange, v3(0, 0, 0.5), 1.57, v3(1, 0, 0));
	arrows.push_back(zArrow);
	handles.push_back(dynamic_pointer_cast<Handle>(zArrow));

	activeAxis = GizmoAxis::NONE;
}

void TranslateGizmoDefinition::TranslateGizmo::query(MeshReference cMesh)
{
	if (state.meshID != cMesh.meshID) {
		state = TranslateGizmoState(cMesh.meshID, cMesh.center);
	}

	checkClicked();

	if (activeAxis == GizmoAxis::NONE)
	{
		if (newPosition != state.position)
		{
			//should add new state here instead
			state.position = newPosition;
		}
		v3 camPos = this->origin().position;
		
		foreach(arrow, getArrowsSortedByDistance())
		{
			v3 center = arrow->mesh.getTrueCenter();
			arrow->distanceFromCam = glm::distance(camPos, center);
			v3 mousePos = camPos + (this->direction * arrow->distanceFromCam);
			float distFromGizmo = glm::distance(mousePos, center);

			if (clicked and distFromGizmo < 0.2)
			{
				clearHover();
				activeAxis = arrow->axis;
				mouseStartOffset = calculateMoveDistance();
				return;
			}
			else {
				if (distFromGizmo < 0.2)
				{
					if (!arrow->hovered)
					{
						clearHover();
						arrow->hovered = true;
					}
					return;
				}
				else {
					arrow->hovered = false;
				}
			}
		}
	}
	else
	{
		translateMesh(cMesh);
	}
}

void TranslateGizmoDefinition::TranslateGizmo::draw()
{
	if (activeAxis != GizmoAxis::NONE)
	{
		arrows[activeAxis]->mesh.uploadOffsetandScaleToGPU();
		arrows[activeAxis]->mesh.renderWithStaticColor(arrows[activeAxis]->activeColor);
	}
	else {
		forall(arrow, arrows)
		{
			arrow->mesh.uploadOffsetandScaleToGPU();
			if (arrow->hovered) {
				arrow->mesh.renderWithStaticColor(arrow->hoverColor);
			}
			else {
				arrow->mesh.render();
			}
		}
	}
}

vector<shared_ptr<TranslateGizmo::Arrow>> TranslateGizmoDefinition::TranslateGizmo::getArrowsSortedByDistance()
{
	vector<shared_ptr<Arrow>> sortedArrows = arrows;
	sort(sortedArrows.begin(), sortedArrows.end(), [](const auto& lhs, const auto& rhs)
	{
		return lhs->distanceFromCam < rhs->distanceFromCam;
	});
	return sortedArrows;
}

glm::vec3 TranslateGizmoDefinition::TranslateGizmo::getCloserPlaneNormal(glm::vec3 position, glm::vec3 center, glm::vec3 normalA, glm::vec3 normalB)
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

float TranslateGizmoDefinition::TranslateGizmo::calculateMoveDistance()
{
	v3 center = state.position;
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
		planeNormal = getCloserPlaneNormal(camPosition, center, normalXY, normalXZ);
		break;
	case GizmoAxis::Y:
		axis = v3(0, 1, 0);
		planeNormal = getCloserPlaneNormal(camPosition, center, normalXY, normalYZ);
		break;
	case GizmoAxis::Z:
		axis = v3(0, 0, 1);
		planeNormal = getCloserPlaneNormal(camPosition, center, normalXZ, normalYZ);
		break;
	default:
		axis = v3(1, 0, 0);
		planeNormal = normalXY;
		break;
	}
	v3 planeIntersect = getRayPlaneIntersect(center, planeNormal, camPosition, this->direction);
	return glm::dot(planeIntersect, axis);
}

void TranslateGizmoDefinition::TranslateGizmo::translateMesh(MeshReference cMesh)
{
	float moveAmount = calculateMoveDistance();
	if (moveAmount != 0)
	{	
		v3 axisVector;
		switch (activeAxis)
		{
			case GizmoAxis::X: axisVector = v3(1, 0, 0); break;
			case GizmoAxis::Y: axisVector = v3(0, 1, 0); break;
			case GizmoAxis::Z: axisVector = v3(0, 0, 1); break;
			default: axisVector = v3(0, 0, 0);
		}
		v3 axisMovement = axisVector * moveAmount;

		newPosition = state.position - mouseStartOffset * axisVector + axisMovement;
		
		forall(arrow, arrows)
		{
			arrow->mesh.offset = newPosition + arrow->offsetFromGizmo;
		}

		v3 meshTranslation = newPosition - cMesh.center;
		switch (activeAxis)
		{
			case GizmoAxis::X: cMesh.translateX(meshTranslation.x); break;
			case GizmoAxis::Y: cMesh.translateY(meshTranslation.y); break;
			case GizmoAxis::Z: cMesh.translateZ(meshTranslation.z); break;
			default: break;
		}

		cMesh.center = newPosition;
	}
}