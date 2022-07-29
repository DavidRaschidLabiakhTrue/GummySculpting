#ifndef Pull_HPP
#define Pull_HPP

#include "SculptAlgos.hpp"
#include "Mesh.hpp"
#include "SculptPayload.hpp"
#include "TopologyComputation.hpp"
#include "Tessellate.hpp"
#include "Brush.hpp"
#include "Inflate.hpp"

namespace Sculpting::Pull
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	using namespace TopologyComputationDefinition;
	using namespace Sculpting;
	void applyPull(MeshReference cMesh, SculptPayloadReference payload);

}

#endif
