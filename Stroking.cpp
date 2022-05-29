#include "Stroking.hpp"
#include "TopologyComputation.hpp"


void Sculpting::Stroking::applyStroke(MeshReference cMesh, SculptPayloadReference payload)
{
	cMesh.octreeRayIntersection(payload.origin, payload.direction);
	
	const auto coll = cMesh.collision;
	if (coll.isCollision == false)
	{
		return; // there was no collision with the octree
	}
	if (coll.triangleID == payload.last)
	{
		return;
	}
	else
	{
		payload.last = coll.triangleID;
	}

	const auto rMult = payload.radius * 0.5f;
	const auto hitPoint = coll.position + rMult;
	const v3 centNormal = cMesh.getTriangleNormal(coll.triangleID);

	const auto rDir = payload.direction * -1.0f; // this flips all axis.


	float falloff = 0; 

	auto& cHistory = cMesh.history.currentChangeLog;

	HistoryKeyVertexMap apply;

	
	cMesh.Octree::collectTrianglesAroundCollision(payload.radius); // perhaps this should return the reference to this below vector to be succint
	auto& triInRange = cMesh.trianglesInRange;



	


	

	Algos::storeCurrentElementsToMap(apply, cHistory, cMesh);

	for (int i = 0; i < 4; i++)
	{
		forall(element, apply)
		{
			element.second.position += rMult * distance(element.second.position, hitPoint) * 0.3f * rDir;
		}
	}

	Algos::applyMapToMesh(apply, cMesh);

	Algos::applySmoothToMapToMesh(apply, cMesh);


	cMesh.updateAffectedTriangles();

	cMesh.history.currentChangeLog.clear();
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