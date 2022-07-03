#include "SmoothedColor.hpp"
#include "SculptAlgos.hpp"
using namespace  Sculpting::Algos;

void Sculpting::SmoothingColor::applySmoothingColor(MeshReference cMesh, SculptPayloadReference payload)
{




	forall(element, cMesh.currentVertices)
	{
		cMesh.currentVertices[element.first].color = cMesh.colorAverageAt(element.first);
	}

	Algos::applyColorfromCurrent(cMesh);


}

