#include "StrokeDirac.hpp"

#include "Camera.hpp"

using CameraDefinition::GlobalCamera;

void Sculpting::StrokingDirac::applyStrokeDirac(MeshReference cMesh, SculptPayloadReference payload, const int iterations)
{
	auto& cHistory = cMesh.history.currentChangeLog;
	HistoryKeyVertexMap apply;

	const auto rMult = payload.radius * 0.5f * 0.3f * payload.hitNorm;
	const auto hitPoint =  + rMult;
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


		element.second.position = element.second.position + reducer * offset * (-0.25f) * element.second.normal;
	}


	Algos::applyMaptoMeshThenApplySmoothedMap(apply, cMesh, 5);

	cMesh.recomputeNormals(apply);
}
