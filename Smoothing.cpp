#include "Smoothing.hpp"



using namespace Sculpting::Smoothing;

// void Sculpting::Smoothing::applySmoothing(MeshReference cMesh, SculptPayloadReference payload)
// {
// 	auto oPayload = cMesh.octreeRayIntersection(payload.origin, payload.direction);

// 	auto& cHistory = cMesh.history.currentChangeLog;
// 	HistoryKeyVertexMap apply;

// 	if (oPayload.isCollision == false)
// 	{
// 		return; // there was no collision with the octree
// 	}
// 	else
// 	{



// 	}
// 	auto list = cMesh.Octree::collectTrianglesAroundCollision(oPayload, payload.radius);



// 	forall(element, list)
// 	{
// 		forall(id, cMesh.triangles[element].indice)
// 		{

// 			apply[id] = cHistory[id] = cMesh.vertices[id];
// 		}

// 	}

// 	forall(element, apply)
// 	{
// 		cMesh.vertices[element.first] = cMesh.averageAt(element.first);
// 	}



// 	cMesh.updateTrianglesInOctree(list);

// 	cMesh.history.currentChangeLog.clear();

// }


void Sculpting::Smoothing::applySmoothing(MeshReference cMesh, SculptPayloadReference payload)
{
	cMesh.octreeRayIntersection(payload.origin, payload.direction);
	auto oPayload = cMesh.collision;

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
	auto list = cMesh.trianglesInRange;



	forall(element, list)
	{
		forall(id, cMesh.triangles[element].indice)
		{

			apply[id] = cHistory[id] = cMesh.vertices[id];
		}

	}

	forall(element, apply)
	{
		cMesh.vertices[element.first] = cMesh.averageAt(element.first);
	}

	cMesh.updateAffectedTriangles();

	cMesh.history.currentChangeLog.clear();

}