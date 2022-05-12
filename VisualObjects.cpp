#include "VisualObjects.hpp"

VisualObjectsDefinition::VisualObjects::VisualObjects()
{
}

VisualObjectsDefinition::VisualObjects::VisualObjects(bool trueConstructor)
{
	this->grid = Grid(TrueConstructor);
}

VisualObjectsDefinition::VisualObjects::~VisualObjects()
{
}

void VisualObjectsDefinition::VisualObjects::drawVisualObjects()
{
	this->grid.drawGrid();
}
