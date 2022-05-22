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

using namespace MathTypeDefinitions;
using namespace Window_Class;

using namespace CameraDefinition;

using namespace RendererDefinition;

using namespace SamplerDefinition;

using namespace GuiDefinition;

using namespace VisualObjectsDefinition;

using namespace SculptBrushDefinition;

class MainProgram
{
	public:
		Empty_Construct MainProgram();

		Construct MainProgram(StringList& arguments);
		Deconstruct ~MainProgram();

		int ProgramCycle();

	private:

		void preprocess(StringList& arguments); // begin preprocessing and setting up resources
		void parseCommandLineArguments(StringList& arguments); // go through command line argument list and read all arguments.

		void loadResources(); // load resources into memory
        void beginDrawFrame(); // begin a draw frame
		void bindGraphicsDataToGPU(); // ensure all meshes are binded to GPU
		void generateMaps(); // generate needed maps on all meshes
		void queryMechanics(); // perform an action query from the user
		void queryCamera(); // query for camera input from the user.

		void draw3D(); // drawing meshes
		void draw2D(); // draw gui and other 2d components

		Window win;
		Camera cam;

		Renderer renderer;

		SculptBrush brush;

		GUI gui;

		VisualObjects visualObjects;


};


#endif


