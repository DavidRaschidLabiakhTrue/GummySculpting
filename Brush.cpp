#include "Brush.hpp"

void Sculpting::Brush::applyBrush(MeshReference cMesh, SculptPayloadReference payload)
{
    //     foreach (vertex, cMesh.currentVertices)
    // {
    //     const float dist = distance(vertex.second.position, payload.hit);
    //     const float curve = ((glm::cos((dist / payload.radius) * pi<float>()) + 1.0f) * 0.5f);
    //     const float scale = 0.05f;

    //     vertex.second.position += payload.polarity *
    //                               payload.radius *
    //                               scale *
    //                               curve *
    //                               payload.hitNorm;
    // }

    const auto hit = payload.hit;
    const float scale = 0.05;

    const auto hitNorm = payload.hitNorm;
    const float radius = payload.radius;

    const float piVal = pi<float>();

    const float brushConst = payload.polarity * payload.radius * scale;

    auto end = cMesh.currentVertices.end();
// parallize
#pragma loop(hint_parallel(8))
    for (auto vertex = cMesh.currentVertices.begin(); vertex != end; ++vertex)
    {
        const float curve = ((glm::cos((distance((*vertex).second.position, payload.hit) / radius) * piVal) + 1.0f) * 0.5f);
        (*vertex).second.position += brushConst * curve * hitNorm;
    }

    Algos::applyCurrentVerticesToMesh(cMesh);
}