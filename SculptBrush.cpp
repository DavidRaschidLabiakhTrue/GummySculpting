#include "SculptBrush.hpp"

#include "Smoothing.hpp"
#include "Coloring.hpp"
#include "Noise.hpp"
#include "Stroking.hpp"

#include "ToolsWindow.hpp"

using namespace SculptBrushDefinition;

using namespace Sculpting;


SculptBrushDefinition::SculptBrush::SculptBrush()
{
}

SculptBrushDefinition::SculptBrush::~SculptBrush()
{
}

SculptBrushDefinition::SculptBrush::SculptBrush(bool trueConstructor) : Sampler(trueConstructor)
{

}

void SculptBrushDefinition::SculptBrush::applySculpt(MeshReference cMesh)
{
	currentDir = direction;
	cMesh.history.sealChange = false;
	payload.direction = this->direction;
	payload.origin = this->origin().position;
	payload.radius = ToolsWindowDefinition::RadiusSlider;

	currentDir = direction;
	switch (this->currentState)
	{
		case BrushState::BrushStateSmooth:

			Smoothing::applySmoothing(cMesh, payload);
			break;

		case BrushState::BrushStateStroke:

			Stroking::applyStroke(cMesh, payload);
			break;

		case BrushState::BrushStateNoise:

			Noising::applyNoise(cMesh, payload);
			break;

		case BrushState::BrushStateColor:

			Coloring::applyColor(cMesh, payload);
			break;
	}

	cMesh.needToRefresh = true;
}

void SculptBrushDefinition::SculptBrush::querySculpt(MeshReference cMesh)
{
	// this logic is faulty and needs revised for proper state mechanics
	if (cast() and this->currentDir != direction)
	{
		applySculpt(cMesh);
	}

	else if (cMesh.history.sealChange == false && CheckMouseReleased(GLFW_MOUSE_BUTTON_LEFT))
	{
		cMesh.history.sealChange = true;
		cMesh.history.adjustLevelUp();

	}



}
