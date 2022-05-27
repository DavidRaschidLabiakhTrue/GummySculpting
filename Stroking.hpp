#ifndef Stroking_HPP
#define Stroking_HPP

#include "Mesh.hpp"
#include "SculptPayload.hpp"
#include "TopologyComputation.hpp"


namespace Sculpting::Stroking
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	using namespace TopologyComputationDefinition;

	void applyStroke(MeshReference cMesh, SculptPayloadReference payload);
}

#endif // !Stroking_HPP

