#ifndef TopBar_HPP
#define TopBar_HPP

#include "Window_API.hpp"
#include "MeshToolsWindow.hpp"
#include "ToolsWindow.hpp"


namespace TopBarDefinition
{
	using namespace Window_API;
	using namespace MeshToolsWindowDefinition;
	using namespace ToolsWindowDefinition;

	// a gui class that enables a top bar in gummy
	class TopBar
	{
		public:
		TopBar();
		~TopBar();

		void build();
		int getHeight();

		MeshToolsWindow meshToolsWindow;
		ToolsWindow toolsWindow;
	};
}

#endif // !TopBar_HPP

