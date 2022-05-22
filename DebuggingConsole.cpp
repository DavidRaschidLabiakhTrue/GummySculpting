#include "DebuggingConsole.hpp"

namespace DebuggingConsoleDefinition
{
	DebuggingConsole console; // globalized
}
	 

using namespace DebuggingConsoleDefinition;


DebuggingConsoleDefinition::DebuggingConsole::DebuggingConsole()
{
}

DebuggingConsoleDefinition::DebuggingConsole::DebuggingConsole(bool trueConstructor)
{
	say "Console Inititalized" done;
}

DebuggingConsoleDefinition::DebuggingConsole::~DebuggingConsole()
{
}
