#include "Debug.hpp"

using namespace DebugLineDefinition;
using namespace DebugPlaneDefinition;

std::vector<DebugLine> lineQueue;
std::vector<DebugPlane> planeQueue;

void Debug::Drawing::drawLine(v3 origin, v3 end, v4 color)
{
	DebugLine newLine = DebugLine(TrueConstructor);
	newLine.setOrigin(origin);
	newLine.setEnd(end);
	newLine.setColor(color);
	lineQueue.push_back(newLine);
}

void Debug::Drawing::renderLines()
{
	forall(line, lineQueue)
	{
		line.drawLine();
	}

	lineQueue.clear();
}

void Debug::Drawing::drawPlane(v3 center, v3 normal, float width, float height, v4 color)
{
	DebugPlane newPlane = DebugPlane(center, normal, width, height, color);
	planeQueue.push_back(newPlane);
}

void Debug::Drawing::renderPlanes()
{
	forall(plane, planeQueue)
	{
		plane.render();
	}

	planeQueue.clear();
}