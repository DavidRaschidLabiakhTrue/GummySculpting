#ifndef Gui_HPP
#define Gui_HPP

#include "Window_API.hpp"


namespace GuiDefinition
{
	using namespace Window_API;

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
	};
}

#endif
