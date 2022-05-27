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
	else
	{



	}
	auto list = cMesh.Octree::collectTrianglesAroundCollision(oPayload, payload.radius);



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
			cMesh.vertices[element.first].position += 0.001f * normalize(cMesh.averageAt(element.first));
		}
	}




	cMesh.updateTrianglesInOctree(list);

	cMesh.history.currentChangeLog.clear();
}
