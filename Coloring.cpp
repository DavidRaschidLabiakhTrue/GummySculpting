#include "Coloring.hpp"
#include "SculptAlgos.hpp"



void Sculpting::Coloring::applyColor(MeshReference cMesh, SculptPayloadReference payload)
{
	auto& cHistory = cMesh.history.currentChangeLog;
	HistoryKeyVertexMap apply;


	Algos::storeCurrentElementsToMap(apply, cHistory, cMesh);



    forall(element, apply)
    {
		element.second.color = ColorSlider_Color_Values;
    }

	Algos::applyColorToMapAndSmoothColor(apply, cMesh);

}
