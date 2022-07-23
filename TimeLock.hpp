#ifndef TimeLock_HPP
#define TimeLock_HPP

#include "TimeGate.hpp"

namespace TimeLock_
{
	using namespace TimeGateDefinition;

	class TimePressLock
	{
		public:
			TimePressLock(int keyCode, double time);
			TimePressLock();
			~TimePressLock();

			void setLockOutTime(double time);
			void update();
			bool canExecute();


		protected:
			int keyType = 0;
			double lastTime = 0.0;
			double timerLockOutDuration = 0.0;

	};
}

#endif

