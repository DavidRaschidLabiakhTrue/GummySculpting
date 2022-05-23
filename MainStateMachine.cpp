#include "MainStateMachine.hpp"

using namespace MainStateMachineDefinition;

MainStateMachineDefinition::MainStateMachine::MainStateMachine()
{
}

MainStateMachineDefinition::MainStateMachine::~MainStateMachine()
{
}

void MainStateMachineDefinition::MainStateMachine::sayStates()
{
	say "Hovering" spc isHovering done;
	say "Mouse Down" spc isMouseDown done;
	say "Focused" spc isFocused done;
	say "Active" spc isFocused done;
	say "Toggle" spc isToggledOpen done;
}
