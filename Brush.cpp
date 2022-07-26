#include "Brush.hpp"

void Sculpting::Brush::applyBrush(MeshReference cMesh, SculptPayloadReference payload)
{
    foreach (vertex, cMesh.currentVertices)
    {
        const float dist = distance(vertex.second.position, payload.hit);
        const float ang = angle(vertex.second.normal, payload.hitNorm);
        const float angLim = glm::radians(60.0f);

        if (ang < angLim)
        {
            float modifier = ((glm::cos((ang / angLim) * pi<float>()) + 1.0f) * 0.5f);

            vertex.second.position += payload.polarity *
                                      (payload.radius * 0.04f) *
                                      ((glm::cos((dist / payload.radius) * pi<float>()) + 1.0f) * 0.5f) *
                                      normalize(modifier * vertex.second.normal + (1 - modifier) * payload.hitNorm);
            //   vertex.second.normal;
            //   normalize((0.75f * vertex.second.normal + 0.25f * payload.direction));
        }
        else
        {
            vertex.second.position += payload.polarity *
                                      (payload.radius * 0.04f) *
                                      ((glm::cos((dist / payload.radius) * pi<float>()) + 1.0f) * 0.5f) *
                                      payload.hitNorm;
        }
    }
    Algos::applyCurrentVerticesToMesh(cMesh);
}