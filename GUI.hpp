#ifndef Gui_HPP
#define Gui_HPP

#include "Window_API.hpp"
#include "TopBar.hpp"
#include "Toolbar.hpp"
#include "CameraNav.hpp"
#include "MeshToolsWindow.hpp"
#include "ToolsWindow.hpp"


namespace GuiDefinition
{
	using namespace Window_API;
	using namespace TopBarDefinition;
	using namespace ToolbarDefinition;
	using namespace CameraNavDefinition;
	using namespace MeshToolsWindowDefinition;
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
			Toolbar toolbar;
			CameraNav cameraNav;
			MeshToolsWindow meshToolsWindow;
			ToolsWindow toolsWindow;
	};
}

#endif
