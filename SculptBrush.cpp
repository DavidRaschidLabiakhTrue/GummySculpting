#include "SculptBrush.hpp"

#include "Coloring.hpp"
#include "DecimateBrush.hpp"
#include "Noise.hpp"
#include "SmoothedColor.hpp"
#include "Smoothing.hpp"
#include "StrokeDirac.hpp"
#include "Stroking.hpp"
#include "Tessellate.hpp"
#include "Inflate.hpp"
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

SculptBrushDefinition::SculptBrush::SculptBrush(bool trueConstructor)
    : Sampler(trueConstructor)
{
    this->offsetTime = glfwGetTime(); // starting up time limiter to sculptor

    sculptRate = 1.0f / 24.0f; // 24 times a second.

	cursor = Cursor3D(true);
}

void SculptBrushDefinition::SculptBrush::querySculpt(MeshReference cMesh)
{
	// this logic is faulty and needs revised for proper state mechanics
	if (cast() and this->currentDir != direction) [[likely]]
	{

		currentDir = direction; // update the current direction

		cMesh.needToStore = false;
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
			//say "beginning PayloadRun" done;

		}
		applySculpt(cMesh);
	}
	else if (cMesh.needToStore == false && CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT))
	{

		// here, the user is done stroking, so if Mesh::savedVertices has size() > 0 vertices, then we should save it to the undo redo queue.
		cMesh.saveSavedVerticesToUndo();
		payload.wasRun = false;


	}


}
void SculptBrushDefinition::SculptBrush::drawCursor()
{

}
void SculptBrushDefinition::SculptBrush::applySculpt(MeshReference cMesh)
{
    cMesh.Octree::collectTrianglesAroundCollision(payload.radius);
	cMesh.storeUndoAndCurrent(); // save the set of vertices we will operate on and save the vertices we wish to possibly undo to.

    switch (this->currentState)
    {
    case BrushState::BrushStateSmooth:

        Smoothing::applySmoothing(cMesh, payload);
        break;

    case BrushState::BrushStateStroke:

        //Stroking::applyStroke(cMesh, payload, 1);
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
        StrokingDirac::applyStrokeDirac(cMesh, payload, 4);
        break;

	case BrushState::BrushInflate:
		Inflate::applyInflate(cMesh, payload, 4);
		break;
	
	case BrushState::BrushFold:

		break;

	case BrushState::BrushSpin:

		break;

    case BrushState::BrushTessellate:
        Tessellate::applyTessellate(cMesh, payload);
        break;

    // case BrushState::BrushDecimate:
    //     Decimate::applyDecimate(cMesh, payload);
    //     break;
    }

    //say "Verifying after sculpt" done;
	//cMesh.verifyMesh(); // Debug
	cMesh.recomputeNormalsFromCurrentVertices();
	cMesh.storeChanged(); // keep a record of all newly changed vertices.
    payload.wasRun = true;
    cMesh.updateAffectedTriangles();
    cMesh.needToRefresh = true;
}
