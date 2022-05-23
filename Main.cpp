

#include "Main.hpp"
#include <iostream>

#include "Window_API.hpp"

Usage Window_API::Window_API_Functions;

int main(int argc, char **argv)
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

MainProgram::MainProgram(StringList &arguments)
{

    win = Window(TrueConstructor);                   // load GLFW and OpenGL.
    Window_Class::WindowGlobal::ActiveWindow = &win; // set up window linkage.
    gui = GUI(TrueConstructor);
    debug = DebugConsoleDefinition::DebugConsole(TrueConstructor);
    // console = DebuggingConsoleDefinition::DebuggingConsole(TrueConstructor);
    CameraDefinition::GlobalCamera = &cam; // set up camera linkage
    brush = SculptBrush(TrueConstructor);

    visualObjects = VisualObjects(TrueConstructor);

    preprocess(arguments);
}

MainProgram::~MainProgram()
{
}

void MainProgram::checkDirectives()
{
    if (Directives.size() != 0)
    {
        say "Directive Detected" done;
        processDirectives();
        Directives.clear();
        say "Directive Exhausted" done;
    }
}

void MainProgram::processDirectives()
{
    /*
    // ytho
    const bool sizeGreaterThan1 = Directives[0].size() > 1; // we have 2 arguments
    const bool sizeGreaterThan2 = Directives[0].size() > 2; // we have 3 arguments
    const bool sizeGreaterThan3 = Directives[0].size() > 3; // we have 4 arguments

    // ^
    string firstArgument = Directives[0][0];
    string secondArgument = (sizeGreaterThan1) ? Directives[0][1] : firstArgument;
    string thirdArgument = (sizeGreaterThan2) ? Directives[0][2] : firstArgument;

    if (sizeGreaterThan1)
    {
        if (firstArgument == "octree")
        {
            if (secondArgument == "rebuild")
            {
                debug.AddLog("Main: Rebuilding Octree");
                renderer.getActiveMesh()->rebuildOctree();
            }
        }
        if (firstArgument == "renderer")
        {
            if (secondArgument == "toggle" && sizeGreaterThan2)
            {
                if (thirdArgument == "wireframe")
                {
                    debug.AddLog("Main: Toggling wireframe Renderer");
                    renderer.toggleWireFrame();
                }
            }

        }
        if (firstArgument == "mesh")
        {

        }
        if (firstArgument == "sculptor")
        {

        }
    }
    */

    using namespace DebugConsoleDefinition;

    vector<string> arguments = Directives[0];
    int numArgs = (int)arguments.size();
    if (numArgs == 0)
    {
        return;
    }

    switch (getCommand(arguments[0]))
    {
    case OCTREE:
        processOctreeCommand(arguments, numArgs);
        break;
    case RENDERER:
        processRendererCommand(arguments, numArgs);
        break;
    case MESH:
        processMeshCommand(arguments, numArgs);
        break;
    case SET:
        processVariableCommand(arguments, numArgs);
        break;
    }
}

void MainProgram::processOctreeCommand(StringList &arguments, int numArgs)
{
    using namespace DebugConsoleDefinition;
    if (numArgs < 2)
    {
        return;
    }

    switch (getCommand(arguments[1]))
    {
    case REBUILD:
        debug.AddLog("Main: Rebuilding Octree");
        renderer.getActiveMesh()->rebuildOctree();
        break;
    case VISUALIZE:
        renderer.getActiveMesh()->visualizeOctree();
        break;
    case TOGGLEWIREFRAME:
        renderer.getActiveMesh()->octreeWireframe.shouldDraw =
            !renderer.getActiveMesh()->octreeWireframe.shouldDraw;
        break;
    case PRINT:
        renderer.getActiveMesh()->octreePrintStats();
        break;
    }
}

void MainProgram::processMeshCommand(StringList &arguments, int numArgs)
{
    using namespace DebugConsoleDefinition;
    if (numArgs < 2)
    {
        return;
    }

    switch (getCommand(arguments[1]))
    {
    case LOOPSUBDIVIDE:
        if (numArgs < 3)
        {
            break;
        }
        // Make sure we have a valid integer
        try
        {
            renderer.getActiveMesh()->loopSubdivision(stoi(arguments[2]));
        }
        catch (exception &e)
        {
            debug.AddLog("Main: Error: Bad Argument: %s", e.what());
            break;
        }
        break;
    case SIMPLESUBDIVIDE:
        if (numArgs < 3)
        {
            break;
        }
        // Make sure we have a valid integer
        try
        {
            renderer.getActiveMesh()->simpleSubdivision4to1(stoi(arguments[2]));
        }
        catch (exception &e)
        {
            debug.AddLog("Main: Error: Bad Argument: %s", e.what());
            break;
        }
        break;
    }
}


void MainProgram::processRendererCommand(StringList &arguments, int numArgs)
{
    using namespace DebugConsoleDefinition;
    if (numArgs < 2)
    {
        return;
    }

    switch (getCommand(arguments[1]))
    {
    case TOGGLE:
        if (numArgs < 3)
        {
            break;
        }

        switch (getCommand(arguments[2]))
        {
        case WIREFRAME:
            debug.AddLog("Main: Toggling wireframe Renderer");
            renderer.toggleWireFrame();
            break;
        }
        break;
    }
}

void MainProgram::processVariableCommand(StringList &arguments, int numArgs)
{
    using namespace DebugConsoleDefinition;
    if (numArgs < 3)
    {
        return;
    }

    auto variableRef = renderer.getActiveMesh()->meshVariables.find(arguments[1]);
	if(variableRef != renderer.getActiveMesh()->meshVariables.end())
	{
		int& variable = get<reference_wrapper<int>>(variableRef->second);
		variable = stoi(arguments[2]);
	}
}

void MainProgram::preprocess(StringList &arguments)
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

        checkDirectives();

        checkDebugConsole();

        queryMechanics(); // query for input

        draw3D(); // drawing meshes
        draw2D();

        eventQuery(); // update glfw in conjunction with opengl
    }

    return 0;
}

void MainProgram::parseCommandLineArguments(StringList &arguments)
{
    string parser = "";
    if (arguments.size() == 0)
    {
        arguments.emplace_back("4star.gum"); // default argument
    }
    else
    {
        foreach (arg, arguments)
        {
            int argSize = (int)arg.size();

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

            if (parser == ".gum")
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
    gui.renderGui();
}
void MainProgram::checkDebugConsole()
{
    if (showDebugConsole)
    {
        debug.Draw(&showDebugConsole);
    }

    if (showDemoDebugger)
    {
        ImGui::ShowDemoWindow(&this->showDemoDebugger);
    }

    gui.buildGuiFrame();
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