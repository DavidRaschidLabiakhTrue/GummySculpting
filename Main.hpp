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


using namespace MathTypeDefinitions;
using namespace Window_Class;

using namespace CameraDefinition;

using namespace RendererDefinition;

using namespace SamplerDefinition;

using namespace GuiDefinition;

using namespace VisualObjectsDefinition;

class MainProgram
{
	public:
		Empty_Construct MainProgram();

		Construct MainProgram(StringList& arguments);
		Deconstruct ~MainProgram();

		int ProgramCycle();

	private:

		void preprocess(StringList& arguments); 
		void parseCommandLineArguments(StringList& arguments);

		void loadResources();
        void beginDrawFrame();
		void bindGraphicsDataToGPU();
		void generateMaps();
		void queryMechanics();
		void queryCamera();

		void draw3D(); // drawing meshes
		void draw2D(); // draw gui and other 2d components

		Window win;
		Camera cam;

		Renderer renderer;

		Sampler sampler;

		GUI gui;

		VisualObjects visualObjects;


};


#endif


