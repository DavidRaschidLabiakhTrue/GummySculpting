#include "Coloring.hpp"

void Sculpting::Coloring::applyColor(MeshReference cMesh, SculptPayloadReference payload)
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

		//say "There was collision with the octree" done;
		// say oPayload.triangleID spc "was hit at distance" spc oPayload.distance spc "with position" spc to_string(oPayload.position) done;

	}
	auto list = cMesh.Octree::collectTrianglesAroundCollision(oPayload, 0.5f);


		forall(element, list)
	{
		forall(id, cMesh.triangles[element].indice)
		{
			if (id > cMesh.vertices.size()) {
				continue;
			}
			apply[id] = cHistory[id] = cMesh.vertices[id];
		}
	
	}
	auto etst = ColorSlider_Color_Values;

	forall(element, apply)
	{
		cMesh.vertices[element.first].loadColorDirectly(ColorSlider_Color_Values);
	}



	cMesh.updateTrianglesInOctree(list);
}
