#ifndef Coloring_HPP
#define Coloring_HPP
// Color.hpp marked for deletion
#include "Mesh.hpp"
#include "SculptPayload.hpp"
namespace Sculpting::Coloring
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;


	void applyColor(MeshReference cMesh, SculptPayloadReference payload); // will be augmented to use a more elaborate color set up and algo.
}
#endif 