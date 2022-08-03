#include "Extrude.hpp"
namespace Sculpting::Extrude
{
    int counter = 0;
    int counterEnd = 4;
}

void Sculpting::Extrude::applyExtrude(MeshReference cMesh, SculptPayloadReference payload)
{
    Sculpting::Extrude::counter = (payload.radius) * 2.0f;

    float thisAvgArea = 0.0f;
    foreach (tri, cMesh.trianglesInRange)
    {
        thisAvgArea += cMesh.getTriangleArea(tri);
    }
    thisAvgArea = thisAvgArea / (float)cMesh.trianglesInRange.size();

    if (thisAvgArea >= payload.radius * 4.0f * cMesh.avgArea)
    {
        bool temp = payload.wasRun;
        payload.wasRun = false;
        Tessellate::applyTessellate(cMesh, payload);
        payload.wasRun = temp;
        cMesh.octreeRayIntersection(payload.origin, payload.direction);
        cMesh.Octree::collectTrianglesAroundCollision(payload.radius);
        cMesh.storeUndoAndCurrent();
    }

    Inflate::applyInflate(cMesh, payload);
    // Brush::applyBrush(cMesh, payload);
    if (++Sculpting::Extrude::counter >= Sculpting::Extrude::counterEnd)
    {
        Sculpting::Extrude::counter = 0;
        cMesh.Octree::collectTrianglesAroundCollision(payload.radius * 1.4f);
        cMesh.storeUndoAndCurrent();
        Algos::applySmoothAndApplyCurrentVerticesToMesh(cMesh, 4);
    }
}