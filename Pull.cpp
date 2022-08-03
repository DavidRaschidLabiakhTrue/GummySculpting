#include "Pull.hpp"
namespace Sculpting::Pull
{
    int counter = 0;
    int counterEnd = 7;
} // namespace Sculpting::Pull

void Sculpting::Pull::applyPull(MeshReference cMesh, SculptPayloadReference payload)
{
    Sculpting::Pull::counterEnd = (4.0f / payload.radius);
    float thisAvgArea = 0.0f;
    foreach (tri, cMesh.trianglesInRange)
    {
        thisAvgArea += cMesh.getTriangleArea(tri);
    }
    thisAvgArea = thisAvgArea / (float)cMesh.trianglesInRange.size();

    if (thisAvgArea >= payload.radius * 5.0f * cMesh.avgArea)
    {
        bool temp = payload.wasRun;
        payload.wasRun = false;
        Tessellate::applyTessellate(cMesh, payload);
        payload.wasRun = temp;
        cMesh.octreeRayIntersection(payload.origin, payload.direction);
        cMesh.Octree::collectTrianglesAroundCollision(payload.radius);
        cMesh.storeUndoAndCurrent();
    }

    // Brush::applyBrush(cMesh, payload);

    // modified brush
    foreach (vertex, cMesh.currentVertices)
    {
        const float dist = distance(vertex.second.position, payload.hit);
        const float curve = ((glm::cos((dist / payload.radius) * pi<float>()) + 1.0f) * 0.5f);
        const float ang = angle(vertex.second.normal, payload.hitNorm);
        const float angLim = glm::radians(60.0f);
        const float scale = 0.05f;

        if (ang < angLim)
        {
            float modifier = ((glm::cos((ang / angLim) * pi<float>()) + 1.0f) * 0.5f);

            vertex.second.position += payload.polarity *
                                      payload.radius *
                                      scale *
                                      curve *
                                      normalize(modifier * vertex.second.normal + (1 - modifier) * payload.hitNorm);
        }
        else
        {
            vertex.second.position += payload.polarity *
                                      payload.radius *
                                      scale *
                                      curve *
                                      payload.hitNorm;
        }
    }
    Algos::applyCurrentVerticesToMesh(cMesh);
    //

    if (++Sculpting::Pull::counter >= Sculpting::Pull::counterEnd)
    {
        Sculpting::Pull::counter = 0;
        cMesh.Octree::collectTrianglesAroundCollision(payload.radius * 1.4f);
        cMesh.storeUndoAndCurrent();
        Algos::applySmoothAndApplyCurrentVerticesToMesh(cMesh, 1);
    }
}