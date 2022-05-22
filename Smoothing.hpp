#ifndef Smoothing_HPP
#define Smoothing_HPP

#include "Mesh.hpp"
#include "SculptPayload.hpp"
// unimplemented still

namespace Sculpting::Smoothing
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;

	void applySmoothing(MeshReference cMesh, SculptPayloadReference payload);


}

#endif
