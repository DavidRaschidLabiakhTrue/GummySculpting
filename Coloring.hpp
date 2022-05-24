#ifndef Coloring_HPP
#define Coloring_HPP
// Color.hpp marked for deletion
#include "Mesh.hpp"

#include "SculptPayload.hpp"

#include "ToolsWindow.hpp"

namespace Sculpting::Coloring
{
	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	using ToolsWindowDefinition::ColorSlider_Color_Values;

	void applyColor(MeshReference cMesh, SculptPayloadReference payload); // will be augmented to use a more elaborate color set up and algo.
}
#endif 