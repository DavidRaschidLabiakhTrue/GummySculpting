#include "SculptBrush.hpp"

#include "Smoothing.hpp"
#include "Coloring.hpp"
#include "Noise.hpp"
#include "Stroking.hpp"

#include "SmoothedColor.hpp"

#include "ToolsWindow.hpp"

using namespace SculptBrushDefinition;

using namespace Sculpting;


SculptBrushDefinition::SculptBrush::SculptBrush()
{
	
}

SculptBrushDefinition::SculptBrush::~SculptBrush()
{
}

SculptBrushDefinition::SculptBrush::SculptBrush(bool trueConstructor) : Sampler(trueConstructor)
{
	this->offsetTime = glfwGetTime(); // starting up time limiter to sculptor

	sculptRate = 1.0f / 24.0f; // 24 times a second.
}

void SculptBrushDefinition::SculptBrush::querySculpt(MeshReference cMesh)
{
	// this logic is faulty and needs revised for proper state mechanics
	if (cast() and this->currentDir != direction)
	{
		currentDir = direction; // update the current direction
		if (payload.wasRun == false) // if the payload has begun a stroke - collect info
		{
			say "beinning PayloadRun" done;

		}
		applySculpt(cMesh);
	}

	else if (cMesh.history.sealChange == false && CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT))
	{
		payload.wasRun = false;

		cMesh.history.sealChange = true;
		cMesh.history.adjustLevelUp();

	}

}
void SculptBrushDefinition::SculptBrush::applySculpt(MeshReference cMesh)
{
	
	cMesh.history.sealChange = false;
	payload.direction = this->direction;
	payload.origin = this->origin().position;
	payload.radius = ToolsWindowDefinition::RadiusSlider;

	cMesh.octreeRayIntersection(payload.origin, payload.direction);
	if (cMesh.collision.isCollision == false or (cMesh.collision.triangleID == payload.last))
	{
		return;
	}
	else
	{
		payload.updateLast(cMesh.collision.triangleID, cMesh.collision.position, cMesh.getTriangleNormal(cMesh.collision.triangleID));
	}
	


	cMesh.Octree::collectTrianglesAroundCollision(payload.radius);

	switch (this->currentState)
	{
		case BrushState::BrushStateSmooth:

			Smoothing::applySmoothing(cMesh, payload);
			break;

		case BrushState::BrushStateStroke:

			Stroking::applyStroke(cMesh, payload, 8);
			break;

		case BrushState::BrushStateNoise:

			Noising::applyNoise(cMesh, payload);
			break;

		case BrushState::BrushStateColor:

			Coloring::applyColor(cMesh, payload);
			break;

		case BrushState::BrushStateSmoothedColor:
			SmoothingColor::applySmoothingColor(cMesh, payload);
			break;
	}
	payload.wasRun = true;
	cMesh.updateAffectedTriangles();

	cMesh.history.currentChangeLog.clear();
	cMesh.needToRefresh = true;
}


