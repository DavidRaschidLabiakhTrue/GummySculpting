#include "StrokeDirac.hpp"

#include "Camera.hpp"

using CameraDefinition::GlobalCamera;

void Sculpting::StrokingDirac::applyStrokeDirac(MeshReference cMesh, SculptPayloadReference payload, const int iterations)
{
    auto &cHistory = cMesh.history.currentChangeLog;
    HistoryKeyVertexMap apply;

    const auto rMult = payload.radius * 0.5f * 0.3f * payload.hitNorm;
    const auto hitPoint = +rMult;
    const auto rDir = payload.direction * -1.0f; // this flips all axis.

    const float sqrRad = payload.radius * payload.radius;
    const float invRad = 1.0f / payload.radius;
    const float power = 40.0f;

    Algos::storeCurrentElementsToMap(apply, cHistory, cMesh);

    const int count = apply.size();
    float reducer;
    float inverter;

    const auto offset = payload.direction * payload.hitNorm * payload.radius;
    forall(element, apply)
    {
        const auto reduc = cMesh.collision.position - element.second.position;
        reducer = glm::sqrt(glm::dot(reduc, reduc)); // l2 norm

		v3 temp = element.second.position;

        element.second.position = element.second.position + reducer * offset * (-0.25f) * element.second.normal;

        if (isnan(cMesh.collision.position.x) || isnan(-cMesh.collision.position.x) ||
            isnan(cMesh.collision.position.y) || isnan(-cMesh.collision.position.y) ||
            isnan(cMesh.collision.position.z) || isnan(-cMesh.collision.position.z) ||
            isnan(element.second.position.x) || isnan(-element.second.position.x) ||
            isnan(element.second.position.y) || isnan(-element.second.position.y) ||
            isnan(element.second.position.z) || isnan(-element.second.position.z) ||
            isnan(reduc.x) || isnan(-reduc.x) ||
            isnan(reduc.y) || isnan(-reduc.y) ||
            isnan(reduc.z) || isnan(-reduc.z) ||
            isnan(reducer) || isnan(-reducer) ||
            isnan(offset.x) || isnan(-offset.x) ||
            isnan(offset.y) || isnan(-offset.y) ||
            isnan(offset.z) || isnan(-offset.z))
        {
            say "Offset: " spc to_string(offset) done;
            say "Collision position:" spc to_string(cMesh.collision.position) done;
            say "element.second.position:" spc to_string(temp) done;
			say "element.second.normal:" spc to_string(element.second.normal) done;
            say "reduc:" spc to_string(reduc) done;
            say "Reducer:" spc to_string(reducer) done;
			say "new element.second.position:" spc to_string(element.second.position) done;
			say "---------------------------------" done;
        }
    }

    Algos::applyMaptoMeshThenApplySmoothedMap(apply, cMesh, 5);

    cMesh.recomputeNormals(apply);
}
