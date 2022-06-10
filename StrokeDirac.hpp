#ifndef StrokeDirac_HPP
#define StrokeDirac_HPP

#include "SculptAlgos.hpp"
#include "Mesh.hpp"
#include "SculptPayload.hpp"
#include "TopologyComputation.hpp"



namespace Sculpting::StrokingDirac
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	using namespace TopologyComputationDefinition;
	using namespace Sculpting;
	void applyStrokeDirac(MeshReference cMesh, SculptPayloadReference payload, const int iterations = 4); // stroke algo based on the dirac delta fn, opperates fundamentally in the same fashion, in the opposite manner.

}

#endif
