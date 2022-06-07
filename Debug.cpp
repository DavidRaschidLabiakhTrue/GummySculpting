#include "Debug.hpp"

using namespace DebugLineDefinition;
using namespace DebugPlaneDefinition;

std::vector<DebugLine> lineQueue;
int numLineDraws;
std::vector<DebugPlane> planeQueue;
int numPlaneDraws;

void Debug::Drawing::drawLine(v3 origin, v3 end, v4 color)
{
	if (numLineDraws >= lineQueue.size())
	{
		DebugLine newLine = DebugLine(TrueConstructor); // this is likely causing a memory leak if the draw ray boolean is true
		newLine.setOrigin(origin);
		newLine.setEnd(end);
		newLine.setColor(color);
		lineQueue.push_back(newLine);
	}
	numLineDraws++;
}

void Debug::Drawing::renderLines()
{
	forall(line, lineQueue)
	{
		line.drawLine();
	}

	numLineDraws = 0;
}

void Debug::Drawing::drawPlane(v3 center, v3 normal, float width, float height, v4 color)
{
	if (numPlaneDraws >= planeQueue.size())
	{
		DebugPlane newPlane = DebugPlane(center, normal, width, height, color);
		planeQueue.push_back(newPlane);
	}
	numPlaneDraws++;
}

void Debug::Drawing::renderPlanes()
{
	forall(plane, planeQueue)
	{
		plane.render();
	}

	numPlaneDraws = 0;
}