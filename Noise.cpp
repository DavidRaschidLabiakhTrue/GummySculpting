#include "Noise.hpp"

#include "glm/gtc/random.hpp"

#include "glm/gtc/noise.hpp"

using glm::linearRand;
using glm::perlin;
using glm::simplex;



// void Sculpting::Noising::applyNoise(MeshReference cMesh, SculptPayloadReference payload)
// {
// 	auto oPayload = cMesh.octreeRayIntersection(payload.origin, payload.direction); // launch an intersection into the tree
// 	auto& cHistory = cMesh.history.currentChangeLog; // start up the change log
// 	HistoryKeyVertexMap apply; // store temporary vertices into this map;

// 	if (oPayload.isCollision == false)
// 	{
// 		return; // there was no collision with the octree
// 	}
// 	else
// 	{

// 	}
// 	auto list = cMesh.Octree::collectTrianglesAroundCollision(oPayload, 0.5f); // get the list of vertices in this range



// 	forall(element, list)
// 	{
// 		forall(id, cMesh.triangles[element].indice)
// 		{
// 			if (id > cMesh.vertices.size())
// 			{
// 				continue; // safety Check
// 			}
// 			apply[id] = cHistory[id] = cMesh.vertices[id]; // load a copy of all id's into 2 maps. One for saving history, and one for apply algos
// 		}

// 	}

// 	forall(element, apply)
// 	{
// 		// element.first is an id value that accesses the vertices of any vertice we collected from octree
// 		// element.second is the vertice itself copied.
// 		//
// 		// // See smoothing and coloring
// 		//
// 		//cMesh.vertices[element.first] = ... // Apply the algo here.
// 	}


// 	cMesh.updateTrianglesInOctree(list);

// 	cMesh.history.currentChangeLog.clear(); // empty out the change log
// }


void Sculpting::Noising::applyNoise(MeshReference cMesh, SculptPayloadReference payload)
{
	cMesh.octreeRayIntersection(payload.origin, payload.direction);
	auto oPayload = cMesh.collision; // launch an intersection into the tree
	auto& cHistory = cMesh.history.currentChangeLog; // start up the change log
	HistoryKeyVertexMap apply; // store temporary vertices into this map;

	if (oPayload.isCollision == false)
	{
		return; // there was no collision with the octree
	}
	else
	{

	}
	cMesh.Octree::collectTrianglesAroundCollision(0.5f);
	auto list = cMesh.trianglesInRange; // get the list of vertices in this range



	forall(element, list)
	{
		forall(id, cMesh.triangles[element].indice)
		{
			if (id > cMesh.vertices.size())
			{
				continue; // safety Check
			}
			apply[id] = cHistory[id] = cMesh.vertices[id]; // load a copy of all id's into 2 maps. One for saving history, and one for apply algos
		}

	}

	forall(element, apply)
	{
		// element.first is an id value that accesses the vertices of any vertice we collected from octree
		// element.second is the vertice itself copied.
		//
		// // See smoothing and coloring
		//
		//cMesh.vertices[element.first] = ... // Apply the algo here.
	}


	cMesh.updateAffectedTriangles();

	cMesh.history.currentChangeLog.clear(); // empty out the change log
}
