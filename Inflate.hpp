#ifndef Inflate_HPP
#define Inflate_HPP

#include "SculptAlgos.hpp"
#include "Mesh.hpp"
#include "SculptPayload.hpp"
#include "TopologyComputation.hpp"

namespace Sculpting::Inflate
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	using namespace TopologyComputationDefinition;
	using namespace Sculpting;
	void applyInflate(MeshReference cMesh, SculptPayloadReference payload, const int iterations = 4);
}

#endif
