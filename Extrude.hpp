#ifndef Extrude_HPP
#define Extrude_HPP

#include "SculptAlgos.hpp"
#include "Mesh.hpp"
#include "SculptPayload.hpp"
#include "TopologyComputation.hpp"
#include "Tessellate.hpp"
#include "Brush.hpp"
#include "Inflate.hpp"

namespace Sculpting::Extrude
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	using namespace TopologyComputationDefinition;
	using namespace Sculpting;
	void applyExtrude(MeshReference cMesh, SculptPayloadReference payload);

}

#endif
