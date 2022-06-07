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
		newLine.shouldDraw = true;
		lineQueue.push_back(newLine);
	}
	else {
		lineQueue[numLineDraws].setOrigin(origin);
		lineQueue[numLineDraws].setEnd(end);
		lineQueue[numLineDraws].setColor(color);
		lineQueue[numLineDraws].shouldDraw = true;
	}
	numLineDraws++;
}

void Debug::Drawing::renderLines()
{
	forall(line, lineQueue)
	{
		if (line.shouldDraw)
		{
			line.drawLine();
		}
		line.shouldDraw = false;
	}

	numLineDraws = 0;
}

void Debug::Drawing::drawPlane(v3 center, v3 normal, float width, float height, v4 color)
{
	if (numPlaneDraws >= planeQueue.size())
	{
		DebugPlane newPlane = DebugPlane(center, normal, width, height, color);
		newPlane.shouldDraw = true;
		planeQueue.push_back(newPlane);
	}
	else {
		planeQueue[numPlaneDraws].calcVertices(center, normal, width, height);
		planeQueue[numPlaneDraws].colorDataUniformly(color);
		planeQueue[numPlaneDraws].shouldDraw = true;
	}
	numPlaneDraws++;
}

void Debug::Drawing::renderPlanes()
{
	forall(plane, planeQueue)
	{
		if (plane.shouldDraw)
		{
			plane.render();
		}
		plane.shouldDraw = false;
	}

	numPlaneDraws = 0;
}