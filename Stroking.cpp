#include "Stroking.hpp"
#include "TopologyComputation.hpp"


void Sculpting::Stroking::applyStroke(MeshReference cMesh, SculptPayloadReference payload)
{
	auto& cHistory = cMesh.history.currentChangeLog;
	HistoryKeyVertexMap apply;

	const auto rMult = payload.radius * 0.5f;
	const auto hitPoint = cMesh.collision.position + rMult;


	const auto rDir = payload.direction * -1.0f; // this flips all axis.



	Algos::storeCurrentElementsToMap(apply, cHistory, cMesh);

	for (int i = 0; i < 4; i++)
	{
		forall(element, apply)
		{
			element.second.position += rMult * distance(element.second.position, hitPoint) * 0.3f * rDir;
		}
	}

	Algos::applyMaptoMeshThenApplySmoothedMap(apply, cMesh);




}



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