#include "SmoothedColor.hpp"

void Sculpting::SmoothingColor::applySmoothingColor(MeshReference cMesh, SculptPayloadReference payload)
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

		//say "There was collision with the octree" done;
		// say oPayload.triangleID spc "was hit at distance" spc oPayload.distance spc "with position" spc to_string(oPayload.position) done;

	}
	cMesh.Octree::collectTrianglesAroundCollision(payload.radius);
	auto list = cMesh.trianglesInRange;


	forall(element, list)
	{
		forall(id, cMesh.triangles[element].indice)
		{


			apply[id] = cHistory[id] = cMesh.vertices[id];
			apply[id].color = cMesh.colorAverageAt(id);
		}

	}
	auto etst = ColorSlider_Color_Values;

	forall(element, apply)
	{

		cMesh.vertices[element.first].color = element.second.color;
	}



	cMesh.updateAffectedTriangles();
}

