

#include <iostream>
#include "Main.hpp"

#include "Window_API.hpp"

Usage Window_API::Window_API_Functions;




int main(int argc, char** argv)
{
    StringList arguments(argv + 1, argv + argc); // loads the arguments as a string vector.

	say "Command Line Arguments:\n\t";
	if (arguments.size() == 0)
	{
		say "No Supplied Arguments, loading defaults\n" done;
	}
	else
	{
		forall(arg, arguments)
		{
			say arg + " ";
		}

	}

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
	gui = GUI(TrueConstructor);
	CameraDefinition::GlobalCamera = &cam; // set up camera linkage
	brush = SculptBrush(TrueConstructor);


	visualObjects = VisualObjects(TrueConstructor);

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

		beginDrawFrame(); // refresh all draw buffers

		queryMechanics(); // query for input
		draw3D(); // drawing meshes
		draw2D();


		eventQuery(); // update glfw in conjunction with opengl

    }


    return 0;
}

void MainProgram::parseCommandLineArguments(StringList& arguments)
{
	string parser = "";
	if (arguments.size() == 0)
	{
		arguments.emplace_back("tetrahedron.gum"); // default argument
	}
	else
	{
		foreach(arg, arguments)
		{
			int argSize = arg.size();

			if (argSize < 4)
			{
				continue;
			}
			else
			{
				
			}
		}
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
	// redundant need to remove
}
void MainProgram::queryMechanics()
{
	queryCamera();
	brush.querySculpt(renderer.getActiveMeshReference());

}
void MainProgram::queryCamera()
{
	cam.checkInput();
	cam.updateMatrix();
}
void MainProgram::draw3D()
{
	renderer.draw();
	brush.drawRay();
	visualObjects.drawVisualObjects();
}
void MainProgram::draw2D()
{
	gui.buildGuiFrame();
	gui.renderGui();
}
void MainProgram::loadResources()
{
	ShaderDefinition::compileGlobalShaders();
}

void MainProgram::beginDrawFrame()
{
	gui.newGuiFrame();
	clearBuffer();
}