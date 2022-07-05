#ifndef SculptAlgos_HPP
#define SculptAlgos_HPP

#include "SculptBrush.hpp"

namespace Sculpting::Algos
{
	using namespace SculptBrushDefinition;

	void applyMaptoMeshThenApplySmoothedMap(HistoryKeyVertexMap& apply, MeshReference cMesh, const int iterations = 7);

	void storeCurrentElementsToMap(HistoryKeyVertexMap& apply, HistoryKeyVertexMap& history, MeshReference cMesh);

	void applyMapToMesh(HistoryKeyVertexMap& apply, MeshReference cMesh);

	void applySmoothToMapToMesh(HistoryKeyVertexMap& apply, MeshReference cMesh, const int iterations = 1);

	void applyColorToMapAndSmoothColor(HistoryKeyVertexMap& apply, MeshReference cMesh);

	void applySmoothToCurrentVertices(MeshReference cMesh, const int iterations = 4);
	void applyCurrentVerticesToMesh(MeshReference cMesh);

	void applySmoothAndApplyCurrentVerticesToMesh(MeshReference cMesh, const int iterations = 4);

	void applyColorfromCurrent(MeshReference cMesh);
}
#endif
