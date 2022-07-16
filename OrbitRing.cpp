#include "OrbitRing.hpp"
using MathTypeDefinitions::CoordinateDefine::rv3;
OrbitRing_::OrbitRing::OrbitRing()
{
}

OrbitRing_::OrbitRing::OrbitRing(int circleResolution, float diameter)
{
	this->resolution = circleResolution;
	this->diameter = diameter;
}

OrbitRing_::OrbitRing::~OrbitRing()
{
}

void OrbitRing_::OrbitRing::generateXYRing()
{
	this->imple.reserve(resolution);
	float heading;


	for (int i = 0; i < resolution; i++)
	{
		heading = glm::radians((float)i);

		imple.emplace_back(v3(cos(heading) * diameter, sin(heading) * diameter, 0.0f));
	}
}

void OrbitRing_::OrbitRing::generateYZRing()
{
	this->imple.reserve(resolution);
}


rv3 OrbitRing_::OrbitRing::left()
{
	int key = internalIndex--;
	if (key < 0)
	{
		internalIndex = resolution - key;
	}
	return imple[getRealIndex(this->internalIndex)];
}

rv3 OrbitRing_::OrbitRing::right()
{
	int key = internalIndex++;
	if (key > resolution)
	{
		internalIndex = key - resolution;
	}
	return imple[getRealIndex(this->internalIndex)];
}

rv3 OrbitRing_::OrbitRing::operator[](int i)
{
	return imple[getRealIndex(internalIndex)];
}

int OrbitRing_::OrbitRing::getRealIndex(int i)
{
	return i;
}
