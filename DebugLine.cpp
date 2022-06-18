#include "DebugLine.hpp"

using namespace DebugLineDefinition;

DebugLineDefinition::DebugLine::DebugLine()
{
}

DebugLineDefinition::DebugLine::DebugLine(bool trueConstructor)
	: RayCast(trueConstructor)
{
}

DebugLine::~DebugLine()
{

}

void DebugLineDefinition::DebugLine::setOrigin(v3 origin)
{
	vertices[0].position = origin;
}

void DebugLineDefinition::DebugLine::setEnd(v3 end)
{
	vertices[1].position = end;
}

void DebugLineDefinition::DebugLine::setColor(v4 color)
{
	colorDataUniformly(color);
}

void DebugLineDefinition::DebugLine::drawLine()
{
	refreshRay();
	drawRay();
}