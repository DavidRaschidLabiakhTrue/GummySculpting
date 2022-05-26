#ifndef SmoothedColor_HPP
#define SmoothedColor_HPP
#include "Mesh.hpp"

#include "SculptPayload.hpp"

#include "ToolsWindow.hpp"
namespace Sculpting::SmoothingColor
{

	using namespace MeshDefinition;
	using namespace SculptPayloadDefinition;
	using ToolsWindowDefinition::ColorSlider_Color_Values;


	void applySmoothingColor(MeshReference cMesh, SculptPayloadReference payload);
}

#endif
