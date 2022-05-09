

#include <iostream>
#include "Main.hpp"

#include "Window_API.hpp"

Usage Window_API::Window_API_Functions;




int main(int argc, char** argv)
{
    StringList arguments(argv + 1, argv + argc); // loads the arguments as a string vector.

    MainProgram mainProgram = MainProgram(arguments);
    



    return mainProgram.ProgramCycle();
}


MainProgram::MainProgram()
{


}

MainProgram::MainProgram(StringList& arguments)
{
    win = Window(TrueConstructor); // load GLFW and OpenGL.
    Window_Class::WindowGlobal::ActiveWindow = &win; // set up window linkage.

	CameraDefinition::GlobalCamera = &cam; // set up camera linkage
	sampler = Sampler(TrueConstructor);
    preprocess(arguments);
}

MainProgram::~MainProgram()
{
}

void MainProgram::preprocess(StringList& arguments)
{
	StringList meshArgument;
	

	parseCommandLineArguments(meshArgument);

	loadResources();
	generateMaps();
	bindGraphicsDataToGPU();

}

int MainProgram::ProgramCycle()
{
    while (shouldNotClose())
    {
		clearBuffer();

		queryMechanics();

		draw3D();
		


		eventQuery();

    }


    return 0;
}

void MainProgram::parseCommandLineArguments(StringList& arguments)
{
	string parser = "";
	if (arguments.size() == 0)
	{
		arguments.emplace_back("sphere.gum"); // default argument
	}

	forall(strArg, arguments)
	{ // check if string can even be a .gum or .obj
		if (strArg.size() > 4)
		{
			parser = strArg.substr(strArg.size() - 4, strArg.size());

			if(parser == ".gum") 
			{ 
				renderer.loadMeshFromFile(strArg);
			} 
			parser.clear();
		}

	}
}
void MainProgram::bindGraphicsDataToGPU()
{
	renderer.bindAllMeshes();
}
void MainProgram::generateMaps()
{

}
void MainProgram::queryMechanics()
{
	queryCamera();
	sampler.queryRay();

}
void MainProgram::queryCamera()
{
	cam.checkInput();
	cam.updateMatrix();
}
void MainProgram::draw3D()
{
	renderer.draw();
	sampler.drawRay();
}
void MainProgram::loadResources()
{
	ShaderDefinition::compileGlobalShaders();
}