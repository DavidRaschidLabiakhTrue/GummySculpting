#include "Smoothing.hpp"



using namespace Sculpting::Smoothing;

void Sculpting::Smoothing::applySmoothing(MeshReference cMesh, SculptPayloadReference payload)
{
	auto key = cMesh.searchLinear(payload.direction,payload.origin);

	auto res = cMesh.octreeRayIntersection(payload.origin, payload.direction);

	if (res.isCollision == false)
	{
		return; // there was no collision with the octree
	}
	else
	{

		//say "There was collision with the octree" done;
		say res.triangleID spc "was hit at distance" spc res.distance spc "with position" spc to_string(res.position) done;
		TriangleIDList triangleList = cMesh.collectTrianglesAroundCollision(res, .01f);
		say "Triangles collected" spc triangleList.size() << ":" done;
		foreach(tid, triangleList) {
			say tid << " ";
		}
	}

	if (key == ImpossibleKey)
	{
		return;
	}
	cMesh.history.changeList[cMesh.history.currentLevelIndex()][key] = V3D(cMesh.averageAt(key));
	cMesh.history.currentChangeLog[key] = V3D(cMesh.averageAt(key));

	forall(edge, cMesh.edges[key].vertexEdges)
	{
		cMesh.history.changeList[cMesh.history.currentLevelIndex()][edge] = V3D(cMesh.averageAt(edge));
		cMesh.history.currentChangeLog[edge] = V3D(cMesh.averageAt(edge));

	}

	// apply changes

	forall(change, cMesh.history.currentChangeLog)
	{
		cMesh.vertices[change.first] = change.second;
	}

	cMesh.history.currentChangeLog.clear();

}


