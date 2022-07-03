#include "Coloring.hpp"
#include "SculptAlgos.hpp"



void Sculpting::Coloring::applyColor(MeshReference cMesh, SculptPayloadReference payload)
{


    forall(element, cMesh.currentVertices)
    {
		element.second.color = ColorSlider_Color_Values;
    }

	Algos::applyColorToMapAndSmoothColor(cMesh.currentVertices, cMesh);

}
