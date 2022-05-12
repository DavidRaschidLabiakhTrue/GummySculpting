#ifndef Gui_HPP
#define Gui_HPP

#include "Window_API.hpp"
#include "TopBar.hpp"


namespace GuiDefinition
{
	using namespace Window_API;
	using namespace TopBarDefinition;

	ImGuiIO& InitializeImGUI();

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
	};
}

#endif
