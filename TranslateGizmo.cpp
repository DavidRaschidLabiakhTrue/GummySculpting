#include "TranslateGizmo.hpp"

TranslateGizmoDefinition::TranslateGizmo::TranslateGizmo()
{
}

TranslateGizmoDefinition::TranslateGizmo::~TranslateGizmo()
{
}

TranslateGizmoDefinition::TranslateGizmo::TranslateGizmo(bool trueConstructor)
{
	//X-axis
	Arrow xArrow = Arrow();
	xArrow.mesh = createGizmoMesh(arrowFileName, GizmoColors::red, v3(-0.5f, 0.0f, 0.0f), 1.57f, GizmoAxes::z, 0.5f);
	xArrow.hoverColor = GizmoColors::lightRed;
	xArrow.activeColor = GizmoColors::lightOrange;
	xArrow.callback = [&](MeshReference cMesh) -> void { translateMesh(cMesh, GizmoAxes::x); };
	arrows.push_back(xArrow);

	//Y-axis
	Arrow yArrow = Arrow();
	yArrow.mesh = createGizmoMesh(arrowFileName, GizmoColors::green, v3(0.0f, 0.5f, 0.0f), 0.0f, GizmoAxes::y, 0.5f);
	yArrow.hoverColor = GizmoColors::lightGreen;
	yArrow.activeColor = GizmoColors::lightOrange;
	yArrow.callback = [&](MeshReference cMesh) -> void { translateMesh(cMesh, GizmoAxes::y); };
	arrows.push_back(yArrow);

	//Z-axis
	Arrow zArrow = Arrow();
	zArrow.mesh = createGizmoMesh(arrowFileName, GizmoColors::blue, v3(0.0f, 0.0f, 0.5f), 1.57f, GizmoAxes::x, 0.5f);
	zArrow.hoverColor = GizmoColors::lightBlue;
	zArrow.activeColor = GizmoColors::lightOrange;
	zArrow.callback = [&](MeshReference cMesh) -> void { translateMesh(cMesh, GizmoAxes::z); };
	arrows.push_back(zArrow);
}

void TranslateGizmoDefinition::TranslateGizmo::query(MeshReference cMesh)
{
	bool clicked = cast();
	if (!clicked)
	{
		screenToWorld();
		active = false;
		activeArrow = NULL;
	}
	if (!active)
	{
		v3 camPos = this->origin().position;

		sortArrowsByDistance();

		forall(arrow, arrows)
		{
			v3 center = arrow.mesh.getTrueCenter();
			arrow.distanceFromCam = glm::distance(camPos, center);
			v3 mousePos = camPos + (this->direction * arrow.distanceFromCam);
			float distFromGizmo = glm::distance(mousePos, center);

			if (clicked and distFromGizmo < 0.2)
			{
				clearHover();
				active = true;
				activeArrow = &arrow;
				return;
			}
			else {
				if (distFromGizmo < 0.2)
				{
					if (!arrow.hovered)
					{
						clearHover();
						arrow.hovered = true;
					}
					return;
				}
				else {
					arrow.hovered = false;
				}
			}
		}
	}
	else if (activeArrow != NULL) 
	{
		activeArrow->callback(cMesh);
	}
}

void TranslateGizmoDefinition::TranslateGizmo::draw()
{
	forall(arrow, arrows)
	{
		arrow.mesh.uploadOffsetandScaleToGPU();
		if (&arrow == activeArrow)
		{
			arrow.mesh.renderWithStaticColor(GizmoColors::lightOrange);
		}
		else if(arrow.hovered) {
			arrow.mesh.renderWithStaticColor(arrow.hoverColor);
		}
		else {
			arrow.mesh.render();
		}
	}
}

void TranslateGizmoDefinition::TranslateGizmo::sortArrowsByDistance()
{
	sort(arrows.begin(), arrows.end(), [](const auto& lhs, const auto& rhs)
	{
		return lhs.distanceFromCam < rhs.distanceFromCam;
	});
}

void TranslateGizmoDefinition::TranslateGizmo::clearHover()
{
	forall(arrow, arrows)
	{
		arrow.hovered = false;
	}
}

void TranslateGizmoDefinition::TranslateGizmo::translateMesh(MeshReference cMesh, v3 axis)
{
	//TODO: Implement a function that translates the current mesh along the given axis based on the mouse movement
	return;
}