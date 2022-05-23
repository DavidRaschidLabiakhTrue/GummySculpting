#ifndef MainStateMachine_HPP
#define MainStateMachine_HPP

#include "Macro.hpp"

namespace MainStateMachineDefinition
{
	using namespace Macros;
	// a collection of boolean variables that gets passed around by reference by main into systems to control their run state.
	struct MainStateMachine
	{
		public:
			MainStateMachine();
			~MainStateMachine();
			void sayStates();

			bool isHovering = false;
			bool isMouseDown = false;
			bool isFocused = false;
			bool isActive = false;

			bool isToggledOpen = false;

			
	};

	typedef MainStateMachine& MainStateReference;
}


#endif // !MainStateMachine_HPP

