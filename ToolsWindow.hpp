#ifndef ToolsWindow_HPP
#define ToolsWindow_HPP

#include "Window_API.hpp"



namespace ToolsWindowDefinition
{
	using namespace Window_API;


	// a gui class that enables a tool window in gummy.
	class ToolsWindow
	{
	public:
		ToolsWindow();
		~ToolsWindow();

		void build();

	};

	extern v4 ColorSlider_Color_Values;
}

#endif // !ToolsWindow_HPP

