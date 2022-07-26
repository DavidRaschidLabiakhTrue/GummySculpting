#ifndef Brush_HPP
#define Brush_HPP

#include "SculptAlgos.hpp"
#include "Mesh.hpp"
#include "SculptPayload.hpp"
#include "TopologyComputation.hpp"

namespace Sculpting::Brush
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	using namespace TopologyComputationDefinition;
	using namespace Sculpting;
	void applyBrush(MeshReference cMesh, SculptPayloadReference payload);

}

#endif
