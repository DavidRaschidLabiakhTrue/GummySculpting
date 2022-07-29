#include "Pull.hpp"
namespace Sculpting::Pull
{
    int counter = 0;
    int counterEnd = 7;
} // namespace Sculpting::Pull

void Sculpting::Pull::applyPull(MeshReference cMesh, SculptPayloadReference payload)
{
    Sculpting::Pull::counterEnd = (5.0f / payload.radius);
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

    Brush::applyBrush(cMesh, payload);
    if (++Sculpting::Pull::counter >= Sculpting::Pull::counterEnd)
    {
        Sculpting::Pull::counter = 0;
        cMesh.Octree::collectTrianglesAroundCollision(payload.radius * 2.0f);
        cMesh.storeUndoAndCurrent();
        Algos::applySmoothAndApplyCurrentVerticesToMesh(cMesh, 2);
    }
}