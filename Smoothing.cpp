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


	forall(element, cMesh.currentVertices)
	{
		//V3D temp = V3D(0,0,0);
		cMesh.vertices[element.first] = cMesh.averageAt(element.first);
		//std::cout << "using smoothing"<< endl; // I don't remember adding this...
	}

	//cMesh.updateAffectedTriangles();
	cMesh.recomputeNormalsFromCurrentVertices();

}

