#include "INodeBox.hpp"

using namespace INodeBoxDefinition;

INodeBoxDefinition::INodeBox::INodeBox()
{
}

INodeBoxDefinition::INodeBox::~INodeBox()
{
}

void INodeBoxDefinition::INodeBox::loadBox(rv3 newCenter, float newHalfSize)
{
	this->boxCenter = newCenter;
	this->boxHalfSize = newHalfSize;
}

v3 INodeBoxDefinition::INodeBox::boxTopFrontLeft()
{
	return v3(boxCenter.x - boxHalfSize, boxCenter.y + boxHalfSize, boxCenter.z + boxHalfSize);
}

v3 INodeBoxDefinition::INodeBox::boxTopFrontRight()
{
	return v3(boxCenter.x + boxHalfSize, boxCenter.y + boxHalfSize, boxCenter.z + boxHalfSize);;
}

v3 INodeBoxDefinition::INodeBox::boxTopBackLeft()
{
	return v3(boxCenter.x - boxHalfSize, boxCenter.y + boxHalfSize, boxCenter.z - boxHalfSize);
}

v3 INodeBoxDefinition::INodeBox::boxTopBackRight()
{
	return v3(boxCenter.x + boxHalfSize, boxCenter.y + boxHalfSize, boxCenter.z - boxHalfSize);
}

v3 INodeBoxDefinition::INodeBox::boxBottomFrontLeft()
{
	return v3(boxCenter.x - boxHalfSize, boxCenter.y - boxHalfSize, boxCenter.z + boxHalfSize);
}

v3 INodeBoxDefinition::INodeBox::boxBottomFrontRight()
{
	return v3(boxCenter.x + boxHalfSize, boxCenter.y - boxHalfSize, boxCenter.z + boxHalfSize);
}

v3 INodeBoxDefinition::INodeBox::boxBottomBackLeft()
{
	return v3(boxCenter.x - boxHalfSize, boxCenter.y - boxHalfSize, boxCenter.z - boxHalfSize);
}

v3 INodeBoxDefinition::INodeBox::boxBottomBackRight()
{
	return v3(boxCenter.x + boxHalfSize, boxCenter.y - boxHalfSize, boxCenter.z - boxHalfSize);
}

float INodeBoxDefinition::INodeBox::halfOfBoxHalfSize()
{
    return this->boxHalfSize * 0.5f;
}
