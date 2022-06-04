#include "TimeGate.hpp"

namespace TimeGateDefinition
{
	double nowTime = 0.0f;

	void tick()
	{
		nowTime = glfwGetTime();
	}
}

using namespace TimeGateDefinition;

TimeGateDefinition::TimeGate::TimeGate() : RATE_INTERVAL(1.0f)
{
}

TimeGateDefinition::TimeGate::TimeGate(double tickInterval) : RATE_INTERVAL(1.0f / tickInterval)
{
	lastTime = 0.0f;
	//this->nowTime = glfwGetTime();
}



void TimeGateDefinition::TimeGate::update()
{
	lastTime = nowTime;
}



const bool TimeGateDefinition::TimeGate::canUpdate()
{
	if ((nowTime - lastTime) >= RATE_INTERVAL)
	{
		lastTime = nowTime;
		return true;
	}
	else
	{
		return false;
	}

}

TimeGateDefinition::TimeGate::~TimeGate()
{
}
