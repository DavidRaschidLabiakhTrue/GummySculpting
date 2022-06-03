#include "TimeGate.hpp"
using namespace TimeGateDefinition;

TimeGateDefinition::TimeGate::TimeGate() : RATE_INTERVAL(1.0f)
{
}

TimeGateDefinition::TimeGate::TimeGate(double tickInterval) : RATE_INTERVAL(1.0f / tickInterval)
{
	lastTime = 0.0f;
	this->nowTime = glfwGetTime();
}

void TimeGateDefinition::TimeGate::begin()
{
	lastTime = 0.0f;
	this->nowTime = glfwGetTime();
}

void TimeGateDefinition::TimeGate::update()
{
	lastTime = nowTime;
}

void TimeGateDefinition::TimeGate::tick()
{
	nowTime = glfwGetTime();
}

const bool TimeGateDefinition::TimeGate::canUpdate()
{
	return (nowTime - lastTime) >= RATE_INTERVAL;
}

TimeGateDefinition::TimeGate::~TimeGate()
{
}
