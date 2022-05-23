#ifndef Gui_HPP
#define Gui_HPP

#include "Window_API.hpp"
#include "TopBar.hpp"
#include "ToolsWindow.hpp"


namespace GuiDefinition
{
	using namespace Window_API;
	using namespace TopBarDefinition;
	using namespace ToolsWindowDefinition;

	ImGuiIO& InitializeImGUI();
	// GUI wrapper class that builds, draws, and renders frames. 
	class GUI
	{
		public:
			GUI();
			GUI(bool trueConstructor);
			~GUI();

			void newGuiFrame();

			void buildGuiFrame();

			void renderGui();

			ImGuiIO imguiIO;

			TopBar topBar;
			ToolsWindow toolsWindow;
	};
}

#endif
