#include "SculptBrush.hpp"

#include "Smoothing.hpp"
#include "Coloring.hpp"
#include "Noise.hpp"
#include "Stroking.hpp"
#include "StrokeDirac.hpp"
#include "SmoothedColor.hpp"
#include "Tessellate.hpp"

#include "ToolsWindow.hpp"

using namespace SculptBrushDefinition;

using namespace Sculpting;
using namespace _Cursor3D;

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

	/*cursor = Cursor(trueConstructor);*/

	cursor = Cursor3D(true);
}

void SculptBrushDefinition::SculptBrush::querySculpt(MeshReference cMesh)
{
	// this logic is faulty and needs revised for proper state mechanics
	if (cast() and this->currentDir != direction) [[likely]]
	{
		
		currentDir = direction; // update the current direction


		cMesh.history.sealChange = false;
		payload.direction = this->direction;
		payload.origin = this->origin().position;
		payload.radius = ToolsWindowDefinition::RadiusSlider;

		cMesh.octreeRayIntersection(payload.origin, payload.direction);

		
		if (cMesh.collision.isCollision == false or (cMesh.collision.triangleID == payload.last))
		{
			cursor.offset = v3(300.0f);
			return;
		}
		else
		{
			cursor.offset = cMesh.collision.position;
			payload.updateLast(cMesh.collision.triangleID, cMesh.collision.position, cMesh.getTriangleNormal(cMesh.collision.triangleID));

		}


		if (payload.wasRun == false) // if the payload has begun a stroke - collect info
		{
			say "beinning PayloadRun" done;

		}
		applySculpt(cMesh);
	}
	else if (cMesh.history.sealChange == false && CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT))
	{
		payload.wasRun = false;
		//cursor.offset = v3(200.0f); // just pop it out of frame.
		cMesh.history.sealChange = true;
		cMesh.history.adjustLevelUp();

	}


}
void SculptBrushDefinition::SculptBrush::drawCursor()
{
	CursorShader.use();
	CursorShader.uploadModelMatrixToGPU(cursor.model);
	CursorShader.uploadOffsetVectorToGPU(cursor.offset);
	cursor.render();
}
void SculptBrushDefinition::SculptBrush::applySculpt(MeshReference cMesh)
{
	cMesh.Octree::collectTrianglesAroundCollision(payload.radius);

	switch (this->currentState)
	{
		case BrushState::BrushStateSmooth:

			Smoothing::applySmoothing(cMesh, payload);
			break;

		case BrushState::BrushStateStroke:

			Stroking::applyStroke(cMesh, payload, 1);
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

		case BrushState::BrushDirac:
			StrokingDirac::applyStrokeDirac(cMesh, payload, 1);
			break;

		case BrushState::BrushTessellate:
			Tessellate::applyTessellate(cMesh, payload);
			break;
	}
	payload.wasRun = true;
	cMesh.updateAffectedTriangles();

	cMesh.history.currentChangeLog.clear();
	cMesh.needToRefresh = true;
}


