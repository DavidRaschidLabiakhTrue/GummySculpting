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

	
	const auto hitPoint = coll.position;
	const v3 centNormal = cMesh.getTriangleNormal(coll.triangleID);

	const auto rDir = payload.direction * -1.0f; // this flips all axis.

	float falloff = 0; 

	auto& cHistory = cMesh.history.currentChangeLog;

	HistoryKeyVertexMap apply;

	
	cMesh.Octree::collectTrianglesAroundCollision(payload.radius);





	


	auto& triInRange = cMesh.trianglesInRange;

	forall(element, triInRange)
	{
		forall(id, cMesh.triangles[element].indice)
		{
			apply[id] = cHistory[id] = cMesh.vertices[id];
		}
	}
	for (int i = 0; i < 4; i++)
	{
		forall(element, apply)
		{
			element.second.position += 0.005f * rDir;
		}
	}

	forall(element, apply)
	{
		cMesh.vertices[element.first].position = element.second.position;
	}



	cMesh.updateAffectedTriangles();

	cMesh.history.currentChangeLog.clear();
}

/*
void Sculpting::Stroking::applyStroke(MeshReference cMesh, SculptPayloadReference payload)
{

	cMesh.octreeRayIntersection(payload.origin, payload.direction);
	OctreeCollision oPayload = cMesh.collision;





	auto& cHistory = cMesh.history.currentChangeLog;
	HistoryKeyVertexMap apply;

	if (oPayload.isCollision == false)
	{
		return; // there was no collision with the octree
	}
	else
	{

	}
	cMesh.Octree::collectTrianglesAroundCollision(payload.radius);
	vector<int> list = cMesh.trianglesInRange;

	forall(element, list)
	{
		forall(id, cMesh.triangles[element].indice)
		{

			apply[id] = cHistory[id] = cMesh.vertices[id];
		}

	}
	for (int i = 0; i < 4; i++)
	{
		forall(element, apply)
		{
			cMesh.vertices[element.first].position += 0.005f * normalize(cMesh.averageAt(element.first));
		}
	}

	forall(element, apply)
	{
		cMesh.vertices[element.first].position = cMesh.averageAt(element.first);
	}




	cMesh.updateAffectedTriangles();

	cMesh.history.currentChangeLog.clear();
}
*/