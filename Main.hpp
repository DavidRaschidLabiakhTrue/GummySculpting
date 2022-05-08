#ifndef Main_HPP
#define Main_HPP

#include "Macro.hpp"
#include "MathDefinitions.hpp"

#include "Window_API.hpp"

#include "Camera.hpp"

#include "Renderer.hpp"

Usage MathTypeDefinitions;
Usage Window_Class;

Usage CameraDefinition;

Usage RendererDefinition;

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
		void bindGraphicsDataToGPU();
		void generateMaps();

		void queryCamera();

		Window win;
		Camera cam;

		Renderer renderer;
};


#endif


