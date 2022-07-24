#include "Inflate.hpp"

void Sculpting::Inflate::applyInflate(MeshReference cMesh, SculptPayloadReference payload, const int iterations)
{

	const auto rMult = payload.radius * 0.5f * 0.3f * payload.hitNorm;
	const auto hitPoint = cMesh.collision.position + rMult;


	const auto rDir = payload.direction * -1.0f; // this flips all axis.





	forall(element, cMesh.currentVertices)
	{
		// element.first is an id value that accesses the vertices of any vertice we collected from octree
		// element.second is the vertice itself copied.
		//
		// // See smoothing and coloring
		//
		//cMesh.vertices[element.first] = ... // Apply the algo here.
		element.second.position += payload.polarity * element.second.normal / 100.0f;
	}
	
	Algos::applySmoothAndApplyCurrentVerticesToMesh(cMesh, 1);

}
