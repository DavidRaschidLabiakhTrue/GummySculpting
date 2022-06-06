#ifndef TimeGate_HPP
#define TimeGate_HPP

#include "Window_API.hpp"

namespace TimeGateDefinition
{
	// gates function call based on time ticks.
	extern double nowTime;
	void tick();
	class TimeGate
	{
		public:

			TimeGate();
			TimeGate(double tickInterval);


			void update();

			const bool canUpdate();

			~TimeGate();

			double lastTime;

			const double RATE_INTERVAL;
	};
}

#endif