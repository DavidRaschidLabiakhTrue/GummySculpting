#include "TimeLock.hpp"
#include "KeyInput.hpp"

using namespace KeyInputDefinition;

TimeLock_::TimePressLock::TimePressLock(int keyCode, double time)
{
	this->keyType = keyCode;
	this->timerLockOutDuration = time;
}

TimeLock_::TimePressLock::TimePressLock()
{
}

TimeLock_::TimePressLock::~TimePressLock()
{
}

void TimeLock_::TimePressLock::setLockOutTime(double time)
{
	this->timerLockOutDuration = time;
}

void TimeLock_::TimePressLock::update()
{
	
}

bool TimeLock_::TimePressLock::canExecute()
{
	if (CheckKeyHeld(this->keyType))
	{

	}
	return false;
}
