#include "Stroking.hpp"

void Sculpting::Stroking::applyStroke(MeshReference cMesh, SculptPayloadReference payload)
{
	auto oPayload = cMesh.octreeRayIntersection(payload.origin, payload.direction);

	auto& cHistory = cMesh.history.currentChangeLog;
	HistoryKeyVertexMap apply;

	if (oPayload.isCollision == false)
	{
		return; // there was no collision with the octree
	}
	auto list = cMesh.Octree::collectTrianglesAroundCollision(oPayload, 0.5f);
	
	v3 average = v3(0);

	forall(element, list)
	{
		forall(id, cMesh.triangles[element].indice)
		{
			apply[id] = cHistory[id] = cMesh.vertices[id];
			average += cMesh.vertices[id].position;
		}

	}

	average = average / (float)(list.size() / 3.0f); // this is wrong but need a base line.

	// this version must be using an interative loop to apply the effects instead.

	float fallOff = 0.5;

	


	forall(element, apply)
	{
		
	}




	cMesh.updateTrianglesInOctree(list);

	cMesh.history.currentChangeLog.clear();
}
