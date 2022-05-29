#ifndef Stroking_HPP
#define Stroking_HPP

#include "SculptAlgos.hpp"
#include "Mesh.hpp"
#include "SculptPayload.hpp"
#include "TopologyComputation.hpp"


namespace Sculpting::Stroking
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	using namespace TopologyComputationDefinition;
	using namespace Sculpting;

	void applyStroke(MeshReference cMesh, SculptPayloadReference payload);
}

#endif // !Stroking_HPP

