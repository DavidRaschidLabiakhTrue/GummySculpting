#include "SculptAlgos.hpp"
using namespace Sculpting::Algos;
void Sculpting::Algos::applyMapToMesh(HistoryKeyVertexMap& apply, MeshReference cMesh)
{
	forall(element, apply)
	{
		cMesh.vertices[element.first] = element.second;
	}
}

void Sculpting::Algos::applySmoothToMapToMesh(HistoryKeyVertexMap& apply, MeshReference cMesh)
{
	forall(element, apply)
	{
		cMesh.vertices[element.first] = cMesh.averageAt(element.first);
	}
}

void Sculpting::Algos::applyMaptoMeshThenApplySmoothedMap(HistoryKeyVertexMap& apply, MeshReference cMesh)
{
	applyMapToMesh(apply, cMesh);
	applySmoothToMapToMesh(apply, cMesh);
}

void Sculpting::Algos::storeCurrentElementsToMap(HistoryKeyVertexMap& apply, HistoryKeyVertexMap& history, MeshReference cMesh)
{
	forall(element, cMesh.trianglesInRange)
	{
		forall(id, cMesh.triangles[element].indice)
		{
			apply[id] = history[id] = cMesh.vertices[id];
		}
	}
}
