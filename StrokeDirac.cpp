#include "StrokeDirac.hpp"

#include "Camera.hpp"

using CameraDefinition::GlobalCamera;

void Sculpting::StrokingDirac::applyStrokeDirac(MeshReference cMesh, SculptPayloadReference payload, const int iterations)
{

    const auto rMult = payload.radius * 0.5f * 0.3f * payload.hitNorm;
    const auto hitPoint = +rMult;
    const auto rDir = payload.direction * -1.0f; // this flips all axis.

    const float sqrRad = payload.radius * payload.radius;
    const float invRad = 1.0f / payload.radius;
    const float power = 40.0f;

    float reducer;
    float inverter;

    const auto offset = payload.direction * payload.hitNorm * payload.radius;
    forall(element, cMesh.currentVertices)
    {
        const auto reduc = cMesh.collision.position - element.second.position;
        reducer = glm::sqrt(glm::dot(reduc, reduc)); // l2 norm

		const float dist = glm::distance(element.second.position, payload.hit) / 50.0f;

        element.second.position += dist * element.second.normal;

    }

	Algos::applySmoothAndApplyCurrentVerticesToMesh(cMesh, 6);
}
