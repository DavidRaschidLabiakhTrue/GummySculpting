#include "SculptAlgos.hpp"
using namespace Sculpting::Algos;
void Sculpting::Algos::applyMapToMesh(HistoryKeyVertexMap& apply, MeshReference cMesh)
{
	forall(element, apply)
	{
		cMesh.vertices[element.first] = element.second;
	}
}

void Sculpting::Algos::applySmoothToMapToMesh(HistoryKeyVertexMap& apply, MeshReference cMesh, const int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		forall(element, apply)
		{
			cMesh.vertices[element.first] = cMesh.averageAt(element.first);
		}
	}

}

void Sculpting::Algos::applyMaptoMeshThenApplySmoothedMap(HistoryKeyVertexMap& apply, MeshReference cMesh, const int iterations)
{
	applyMapToMesh(apply, cMesh);
	applySmoothToMapToMesh(apply, cMesh, iterations);
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



void Sculpting::Algos::applySmoothToCurrentVertices(MeshReference cMesh, const int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		forall(element, cMesh.currentVertices)
		{
			cMesh.vertices[element.first] = cMesh.averageAt(element.first);
		}
	}
}

void Sculpting::Algos::applyCurrentVerticesToMesh(MeshReference cMesh)
{
	forall(element, cMesh.currentVertices)
	{
		cMesh.vertices[element.first] = element.second;
	}
}

void Sculpting::Algos::applySmoothAndApplyCurrentVerticesToMesh(MeshReference cMesh, const int iterations)
{
	applyCurrentVerticesToMesh(cMesh);
	applySmoothToCurrentVertices(cMesh, iterations);
	
}

void Sculpting::Algos::applyColorfromCurrent(MeshReference cMesh)
{
	forall(element, cMesh.currentVertices)
	{
		cMesh.vertices[element.first].color = element.second.color;
	}
}



void Sculpting::Algos::applyColorToMapAndSmoothColor(HistoryKeyVertexMap& apply, MeshReference cMesh)
{
	forall(element, apply)
	{
		cMesh.vertices[element.first].color = element.second.color;
	}
	forall(element, apply)
	{
		cMesh.vertices[element.first].color = cMesh.colorAverageAt(element.first);
	}
}
