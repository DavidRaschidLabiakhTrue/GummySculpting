#include "Stroking.hpp"






void Sculpting::Stroking::applyStroke(MeshReference cMesh, SculptPayloadReference payload)
{
	SculptPayload payloadSym = payload;
	/*
	bool canSymmetric;
	canSymmetric = TopologyComputationDefinition::swapRayAxisAndOrigin(payload.direction, payload.origin, payloadSym.origin, payloadSym.direction);
	*/
	OctreeCollision oPayload = cMesh.octreeRayIntersection(payload.origin, payload.direction);

	/*
	OctreeCollision oPayload2;

	if (canSymmetric)
	{
		oPayload2 = cMesh.octreeRayIntersection(payloadSym.origin, payloadSym.direction);
	}
	*/



	auto& cHistory = cMesh.history.currentChangeLog;
	HistoryKeyVertexMap apply;

	if (oPayload.isCollision == false)
	{
		return; // there was no collision with the octree
	}
	else
	{
		
	}
	vector<int> list = cMesh.Octree::collectTrianglesAroundCollision(oPayload, payload.radius);
	/*
	vector<int> list2;
	if (canSymmetric and oPayload2.isCollision)
	{
		list2 = cMesh.Octree::collectTrianglesAroundCollision(oPayload2, payload.radius);
		list.insert(list.end(), list2.begin(), list2.end());
	}
	

	list.insert(list.end(), list2.begin(), list2.end());
	*/
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




	cMesh.updateTrianglesInOctree(list);

	cMesh.history.currentChangeLog.clear();
}
