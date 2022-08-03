#include "Brush.hpp"

void Sculpting::Brush::applyBrush(MeshReference cMesh, SculptPayloadReference payload)
{
    foreach (vertex, cMesh.currentVertices)
    {
        const float dist = distance(vertex.second.position, payload.hit);
        const float curve = ((glm::cos((dist / payload.radius) * pi<float>()) + 1.0f) * 0.5f);
        const float scale = 0.05f;

        vertex.second.position += payload.polarity *
                                  payload.radius *
                                  scale *
                                  curve *
                                  payload.hitNorm;
    }
    Algos::applyCurrentVerticesToMesh(cMesh);
}