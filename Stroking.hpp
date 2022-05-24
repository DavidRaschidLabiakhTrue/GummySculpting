#ifndef Stroking_HPP
#define Stroking_HPP

#include "Mesh.hpp"
#include "SculptPayload.hpp"

namespace Sculpting::Stroking
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	void applyStroke(MeshReference cMesh, SculptPayloadReference payload);
}

#endif // !Stroking_HPP

