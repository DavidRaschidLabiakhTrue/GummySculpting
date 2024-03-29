#include "SculptBrush.hpp"

#include "Brush.hpp"
#include "Coloring.hpp"
#include "DecimateBrush.hpp"
#include "Extrude.hpp"
#include "Inflate.hpp"
#include "Noise.hpp"
#include "Pull.hpp"
#include "SmoothedColor.hpp"
#include "Smoothing.hpp"
#include "StrokeDirac.hpp"
#include "Stroking.hpp"
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
        // for when the user selects a mesh.
        if (this->currentState == BrushState::BrushProcessSelect) [[unlikely]]
        {
            MainDirectiveDefinition::Directives.push_back({"mesh", "beginSelect"});
            this->payload.selectionOrigin = this->origin().position;
            this->payload.direction = this->direction;
            return;
        }
        payload.modifyPolarity();
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
            // say "beginning PayloadRun" done;
        }
        applySculpt(cMesh);
    }
    else if (cMesh.needToStore == false && CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT))
    {

        // here, the user is done stroking, so if Mesh::savedVertices has size() > 0 vertices, then we should save it to the undo redo queue.
        if (this->currentState == BrushState::BrushPull)
        {
            Algos::applySmoothAndApplyCurrentVerticesToMesh(cMesh, 2);
            cMesh.updateAffectedTriangles();
            cMesh.computeNormals();
            cMesh.storeChanged(); // keep a record of all newly changed vertices.
            cMesh.needToRefresh = true;
        }
        else if (this->currentState != BrushState::BrushPull &&
                 this->currentState != BrushState::BrushExtrude &&
                 this->currentState != BrushState::BrushStateColor &&
                 this->currentState != BrushState::BrushStateSmoothedColor)
        {
            cMesh.computeAverageArea();
        }

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
    // cMesh.collectAroundCollision(payload.radius, true);
    cMesh.storeUndoAndCurrent(); // save the set of vertices we will operate on and save the vertices we wish to possibly undo to.

    switch (this->currentState)
    {
    case BrushState::BrushStateSmooth:

        Smoothing::applySmoothing(cMesh, payload);
        break;

    case BrushState::BrushStateStroke:

        // Stroking::applyStroke(cMesh, payload, 1);
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
    case BrushState::BrushBrush:
        Brush::applyBrush(cMesh, payload);
        break;
    case BrushState::BrushExtrude:
        Extrude::applyExtrude(cMesh, payload);
        handleDynamicVertexIndexModification();
        break;
    case BrushState::BrushPull:
        Pull::applyPull(cMesh, payload);
        handleDynamicVertexIndexModification();
        break;

    case BrushState::BrushFold:

        break;

    case BrushState::BrushSpin:

        break;

    case BrushState::BrushTessellate:
        Tessellate::applyTessellate(cMesh, payload);
        handleDynamicVertexIndexModification();
        break;

        // case BrushState::BrushDecimate:
        //     Decimate::applyDecimate(cMesh, payload);
        //     break;
    }

    // say "Verifying after sculpt" done;
    // cMesh.verifyMesh(); // Debug
    //  cMesh.recomputeNormalsFromCurrentVertices();
    cMesh.computeNormals();
    cMesh.storeChanged(); // keep a record of all newly changed vertices.
    payload.wasRun = true;
    cMesh.updateAffectedTriangles();
    cMesh.needToRefresh = true;

    if (this->currentState == BrushState::BrushExtrude ||
        this->currentState == BrushState::BrushPull)
    {
        payload.last = -1;
		this->currentDir = v3(0.0f);
        payload.wasRun = false;
    }
}
