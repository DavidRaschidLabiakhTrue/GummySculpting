#ifndef TimeGate_HPP
#define TimeGate_HPP

#include "Window_API.hpp"

namespace TimeGateDefinition
{
	// gates function call based on time ticks.
	class TimeGate
	{
		public:

			TimeGate();
			TimeGate(double tickInterval);

			void begin();
			void update();
			void tick();
			const bool canUpdate();

			~TimeGate();

			double lastTime;
			double nowTime;
			const double RATE_INTERVAL;
	};
}

#endif