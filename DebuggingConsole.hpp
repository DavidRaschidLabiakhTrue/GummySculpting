#ifndef DebuggingConsole_HPP
#define DebuggingConsole_HPP

#include "MainDirective.hpp"
#include "Window_API.hpp"
#include <unordered_map>

// this is the most cursed file in the entire project and I do not recommend touching it for any reason or trying to understand it. It's bad.

namespace DebugConsoleDefinition
{
// C++ BLACK MAGIC DO NOT USE
#define DYNAMIC_DEBUG_CONSOLE_IMPLEMENTATION \
    struct Impl;                             \
    Impl *self;

    static int Game_Stricmp(const char *s1, const char *s2)
    {
        int d;
        while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
        {
            s1++;
            s2++;
        }
        return d;
    }
    static int Game_Strnicmp(const char *s1, const char *s2, int n)
    {
        int d = 0;
        while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
        {
            s1++;
            s2++;
            n--;
        }
        return d;
    }
    static char *Game_Strdup(const char *s)
    {
        IM_ASSERT(s);
        size_t len = strlen(s) + 1;
        void *buf = malloc(len);
        IM_ASSERT(buf);
        return (char *)memcpy(buf, (const void *)s, len);
    }
    static void Game_Strtrim(char *s)
    {
        char *str_end = s + strlen(s);
        while (str_end > s && str_end[-1] == ' ')
            str_end--;
        *str_end = 0;
    }

    // Add Commands to map and enum for access in switch statement
    enum CONSOLECOMMAND
    {
        UNKNOWN = -1,
        SHOWME,
        EXIT,
        OCTREE,
        MESH,
        RENDERER,
        SCULPTOR,
        REBUILD,
        VISUALIZE,
        TOGGLE,
        WIREFRAME,
        TOGGLEWIREFRAME,
        LOOPSUBDIVIDE,
        SIMPLESUBDIVIDE,
        PRINT,
        SET,
        DEBUG,
        SETTINGS,
        UNDO,
        REDO,
        DEMO,
        SMOOTH,
        STROKE,
        COLOR,
        NOISE,
        DIRAC,
        SMOOTHEDCOLOR,
        SUBDLEVEL,
        IMPORT,
        EXPORT,
        FILEMANGEMENT,
        DRAWMODE,
        ALLOCTANTS,
        LEAFOCTANTS,
        INTERSECTEDOCTANTS,
        INTERSECTEDLEAFOCTANTS,
        BRUSH,
        EXTRUDE,
        PULL,
        TESSELLATE,
        DECIMATE,
        REMESH,
		INFLATE,
		SPIN,
		FOLD,
		SELECT,
		BEGINSELECT,
		DELETECURRENT,
    };

    const unordered_map<string, CONSOLECOMMAND> commandMap = {
        {"showme", SHOWME},
        {"exit", EXIT},
        {"octree", OCTREE},
        {"mesh", MESH},
        {"renderer", RENDERER},
        {"sculptor", SCULPTOR},
        {"rebuild", REBUILD},
        {"visualize", VISUALIZE},
        {"toggle", TOGGLE},
        {"wireframe", WIREFRAME},
        {"togglewireframe", TOGGLEWIREFRAME},
        {"loopsubdivide", LOOPSUBDIVIDE},
        {"simplesubdivide", SIMPLESUBDIVIDE},
        {"print", PRINT},
        {"set", SET},
        {"debug", DEBUG},
        {"settings", SETTINGS},
        {"undo", UNDO},
        {"redo", REDO},
        {"demo", DEMO},
        {"smooth", SMOOTH},
        {"color", COLOR},
        {"stroke", STROKE},
        {"brush", BRUSH},
        {"pull", PULL},
        {"extrude", EXTRUDE},
        {"noise", NOISE},
        {"smoothedcolor", SMOOTHEDCOLOR},
        {"subdlevel", SUBDLEVEL},
        {"file", FILEMANGEMENT},
        {"import", IMPORT},
        {"export", EXPORT},
        {"dirac", DIRAC},
        {"drawmode", DRAWMODE},
        {"alloctants", ALLOCTANTS},
        {"leafoctants", LEAFOCTANTS},
        {"intersectedoctants", INTERSECTEDOCTANTS},
        {"intersectedleafoctants", INTERSECTEDLEAFOCTANTS},
        {"tessellate", TESSELLATE},
        {"decimate", DECIMATE},
        {"remesh", REMESH},
		{"inflate", INFLATE},
		{"spin", SPIN},
		{"fold", FOLD},
		{"select", SELECT},
		{"beginSelect", BEGINSELECT},
		{"deleteCurrent", DELETECURRENT}

    };

    static CONSOLECOMMAND getCommand(string command)
    {
        auto it = commandMap.find(command);
        if (it != commandMap.end())
        {
            return (CONSOLECOMMAND)it->second;
        }
        else
        {
            return UNKNOWN;
        }
    }

    // this implementation of a debugging console is based off an old design of David. It's based partially on ImGUI's demo but makes multiple changes to use std data structures
    // this is not being designed to be more neat and clean without dynamic allocation like everything else in the program.
    class DebugConsole
    {
        public:
            DebugConsole();
            DebugConsole(bool trueConstructor);
            ~DebugConsole();

            void AddLog(const char *fmt, ...); // adds a log to the view console - reliant on dynamic allocation - beware
            void CleanConsole();

            void Draw(bool *p_open);

        private:
            static int TextEditCallbackStub(ImGuiInputTextCallbackData *data);
            int TextEditCallback(ImGuiInputTextCallbackData *data);
            void ExecCommand(const char *command_line);
            const char *title = "Debug Console";
            void implementDebugConsole(); // the actual allocator function
            bool execCommandLine(const char *command_line);
            DYNAMIC_DEBUG_CONSOLE_IMPLEMENTATION; // DO NOT REPLICATE THIS CODE - IT'S WITCH CRAFT
    };

    extern DebugConsole debug;

} // namespace DebugConsoleDefinition

#endif
