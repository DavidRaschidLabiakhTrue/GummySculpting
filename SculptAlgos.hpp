#ifndef SculptAlgos_HPP
#define SculptAlgos_HPP

#include "SculptBrush.hpp"

namespace Sculpting::Algos
{
	using namespace SculptBrushDefinition;

	void applyMaptoMeshThenApplySmoothedMap(HistoryKeyVertexMap& apply, MeshReference cMesh);

	void storeCurrentElementsToMap(HistoryKeyVertexMap& apply, HistoryKeyVertexMap& history, MeshReference cMesh);

	void applyMapToMesh(HistoryKeyVertexMap& apply, MeshReference cMesh);

	void applySmoothToMapToMesh(HistoryKeyVertexMap& apply, MeshReference cMesh, const int iterations = 1);

	void applyColorToMapAndSmoothColor(HistoryKeyVertexMap& apply, MeshReference cMesh);

}
#endif
