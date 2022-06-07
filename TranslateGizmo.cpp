#include "TranslateGizmo.hpp"

using namespace MathTypeDefinitions;



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

	//X-axis
	shared_ptr<Arrow> zArrow = make_shared<Arrow>(GizmoAxis::Z, GizmoColors::blue, GizmoColors::lightBlue,
		GizmoColors::lightOrange, v3(0, 0, 0.5), 1.57, v3(1, 0, 0));
	arrows.push_back(zArrow);
	handles.push_back(dynamic_pointer_cast<Handle>(zArrow));

	activeAxis = GizmoAxis::NONE;
}

void TranslateGizmoDefinition::TranslateGizmo::query(MeshReference cMesh)
{
	bool clicked = cast();
	if (!clicked)
	{
		screenToWorld();
		active = false;
		activeAxis = GizmoAxis::NONE;
	}
	if (!active)
	{
		v3 camPos = this->origin().position;

		sortArrowsByDistance();
		
		foreach(arrow, arrows)
		{
			v3 center = arrow->mesh.getTrueCenter();
			
			arrow->distanceFromCam = glm::distance(camPos, center);
			v3 mousePos = camPos + (this->direction * arrow->distanceFromCam);
			float distFromGizmo = glm::distance(mousePos, center);

			if (clicked and distFromGizmo < 0.2)
			{
				clearHover();
				active = true;
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
	
	else if (activeAxis != GizmoAxis::NONE)
	{
		translateMesh(cMesh);
	}
}

void TranslateGizmoDefinition::TranslateGizmo::draw()
{
	forall(arrow, arrows)
	{
		say arrow->test2 done;
			
		arrow->mesh.uploadOffsetandScaleToGPU();
		if (arrow->axis == activeAxis)
		{
			arrow->mesh.renderWithStaticColor(GizmoColors::lightOrange);
		}
		else if (arrow->hovered) {
			arrow->mesh.renderWithStaticColor(arrow->hoverColor);
		}
		else {
			arrow->mesh.render();
		}
	}
}

void TranslateGizmoDefinition::TranslateGizmo::sortArrowsByDistance()
{
	sort(arrows.begin(), arrows.end(), [](const auto& lhs, const auto& rhs)
	{
		return lhs->distanceFromCam < rhs->distanceFromCam;
	});
}

void TranslateGizmoDefinition::TranslateGizmo::clearHover()
{
	forall(arrow, arrows)
	{
		arrow->hovered = false;
	}
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
	v3 center = v3(0,0,0);
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
		/*
		//check to initialize next state
		if (!state->next_state)
		{
			state->next_state = make_shared<TranslateGizmoState>(cMesh);
			state->next_state->next_state = nullptr;
			state->next_state->prev_state = state;
			//don't switch to next state yet
		}
		*/
		
		v3 axisMovement;
		switch (activeAxis)
		{
			case GizmoAxis::X: axisMovement = v3(1, 0, 0) * moveAmount; break;
			case GizmoAxis::Y: axisMovement = v3(0, 1, 0) * moveAmount; break;
			case GizmoAxis::Z: axisMovement = v3(0, 0, 1) * moveAmount; break;
			default: axisMovement = v3(0, 0, 0);
		}

		Debug::Drawing::drawLine(v3(0, 0, 0), axisMovement);

		/*
		state->next_state->position = state->position + axisMovement;

		forall(arrow, arrows)
		{
			arrow->mesh.offset = state->position + axisMovement + arrow->offsetFromGizmo;
		}
		*/
		
	}
}