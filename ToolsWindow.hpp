#ifndef ToolsWindow_HPP
#define ToolsWindow_HPP

#include "Window_API.hpp"



namespace ToolsWindowDefinition
{
	using namespace Window_API;

	// a gui class that enables a top bar in gummy
	class ToolsWindow
	{
	public:
		ToolsWindow();
		~ToolsWindow();

		void build();


	};
}

#endif // !ToolsWindow_HPP

