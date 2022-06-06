#ifndef Main_HPP
#define Main_HPP

#include "Macro.hpp"
#include "MathDefinitions.hpp"

#include "Window_API.hpp"

#include "Camera.hpp"

#include "Renderer.hpp"

#include "Sampler.hpp"


#include "GUI.hpp"

#include "VisualObjects.hpp"

#include "SculptBrush.hpp"

#include "GizmoManager.hpp"

#include "DebuggingConsole.hpp"

#include "MainDirective.hpp"

#include "TimeGate.hpp"

#include <variant>

using namespace MathTypeDefinitions;
using namespace Window_Class;

using namespace CameraDefinition;

using namespace RendererDefinition;

using namespace SamplerDefinition;

using namespace GuiDefinition;

using namespace VisualObjectsDefinition;

using namespace SculptBrushDefinition;

using namespace GizmoManagerDefinition;

using namespace TimeGateDefinition;

using DebugConsoleDefinition::debug;

using MainDirectiveDefinition::Directives; // command list main must execute

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
class MainProgram
{
	public:
		Empty_Construct MainProgram();

		Construct MainProgram(StringList& arguments);
		Deconstruct ~MainProgram();

		int ProgramCycle();

	private:



		void checkDirectives();
		void processDirectives();
		void preprocess(StringList& arguments); // begin preprocessing and setting up resources
		void parseCommandLineArguments(StringList& arguments); // go through command line argument list and read all arguments.
		void processOctreeCommand(StringList& arguments, int numArgs); // process octree command
		void processRendererCommand(StringList& arguments, int numArgs); // process renderer command
		void processMeshCommand(StringList& arguments, int numArgs); // process mesh command
		void processVariableCommand(StringList& arguments, int numArgs); // process variable command
		void processFileManagementCommand(StringList& arguments, int numArgs);
		// pair< getVariable()

		void processSculptorCommand(StringList& arguments, int numArgs);

		void processDebugCommand(StringList& arguments, int numArgs);

		void loadResources(); // load resources into memory
        void beginDrawFrame(); // begin a draw frame
		void bindGraphicsDataToGPU(); // ensure all meshes are binded to GPU
		void generateMaps(); // generate needed maps on all meshes
		void queryMechanics(); // perform an action query from the user
		void queryCamera(); // query for camera input from the user.

		void draw3D(); // drawing meshes

		void drawStatic();
		void draw2D(); // draw gui and other 2d components
		void checkDebugConsole();

		void buildGuiFrame();

		Window win;
		Camera cam;

		Renderer renderer;

		SculptBrush brush;

		GizmoManager gizmoManager;

		GUI gui;

		bool showDebugConsole = false;
		bool showDemoDebugger = false;
		VisualObjects visualObjects;

		TimeGate cameraGate = TimeGate(30);
		TimeGate sculptGate = TimeGate(5.0f);
		TimeGate renderGate = TimeGate(45.0f);


};


#endif


