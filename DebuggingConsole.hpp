#ifndef DebuggingConsole_HPP
#define DebuggingConsole_HPP

#include "Window_API.hpp"

namespace DebuggingConsoleDefinition
{
	using namespace Window_API;

	class DebuggingConsole
	{
		public:
			DebuggingConsole();
			DebuggingConsole(bool trueConstructor);
			~DebuggingConsole();
			char InputBuf[256]; // text input buffer;



	};

	extern DebuggingConsole console;

}

#endif
