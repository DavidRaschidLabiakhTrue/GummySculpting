#include "Debug.hpp"

using namespace DebugLineDefinition;

std::vector<DebugLine> lineQueue;

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