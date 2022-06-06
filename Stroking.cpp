#include "Stroking.hpp"
#include "TopologyComputation.hpp"


void Sculpting::Stroking::applyStroke(MeshReference cMesh, SculptPayloadReference payload, const int iterations)
{
	auto& cHistory = cMesh.history.currentChangeLog;
	HistoryKeyVertexMap apply;

	const auto rMult = payload.radius * 0.5f * 0.3f * payload.hitNorm;
	const auto hitPoint = cMesh.collision.position + rMult;


	const auto rDir = payload.direction * -1.0f; // this flips all axis.

	// say to_string(payload.hitNorm) done;


	Algos::storeCurrentElementsToMap(apply, cHistory, cMesh);
	Algos::applyMaptoMeshThenApplySmoothedMap(apply, cMesh, 1);
	for (int i = 0; i < iterations; i++)
	{
		forall(element, apply)
		{
			element.second.position += rMult * distance(element.second.position, hitPoint) ;
		}
	}

	Algos::applyMaptoMeshThenApplySmoothedMap(apply, cMesh, 1);

	cMesh.recomputeNormals(apply);


}

/*
* // STRETCH TO NORM
* 	for (int i = 0; i < 4; i++)
	{
		forall(element, apply)
		{
			element.second.position += rMult * distance(element.second.position, hitPoint) * 0.3f * payload.hitNorm;
		}
	}
*/

/*
*  // CRATER ALGO
* 	for (int i = 0; i < 4; i++)
	{
		forall(element, apply)
		{
			element.second.position += rMult * distance(element.second.position, hitPoint) * rDir;
		}
	}
*/