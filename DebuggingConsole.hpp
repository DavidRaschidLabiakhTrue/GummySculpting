#ifndef DebuggingConsole_HPP
#define DebuggingConsole_HPP

#include "Window_API.hpp"
#include "MainDirective.hpp"

// this is the most cursed file in the entire project and I do not recommend touching it for any reason or trying to understand it. It's bad.

namespace DebugConsoleDefinition
{
	// C++ BLACK MAGIC DO NOT USE
	#define DYNAMIC_DEBUG_CONSOLE_IMPLEMENTATION struct Impl; Impl* self;


	// 
	static int   Game_Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
	static int   Game_Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
	static char* Game_Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
	static void  Game_Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

	// this implementation of a debugging console is based off an old design of David. It's based partially on ImGUI's demo but makes multiple changes to use std data structures
	// this is not being designed to be more neat and clean without dynamic allocation like everything else in the program.
	class DebugConsole
	{
		public:
			DebugConsole();
			DebugConsole(bool trueConstructor);
			~DebugConsole();

			void AddLog(const char* fmt, ...); // adds a log to the view console - reliant on dynamic allocation - beware
			void CleanConsole();


			void Draw(bool* p_open);


			

		private:
			static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
			int TextEditCallback(ImGuiInputTextCallbackData* data);
			void ExecCommand(const char* command_line);
			const char* title = "Debug Console";
			void implementDebugConsole(); // the actual allocator function
			DYNAMIC_DEBUG_CONSOLE_IMPLEMENTATION; // DO NOT REPLICATE THIS CODE - IT'S WITCH CRAFT
	};

	extern DebugConsole debug;

	  
}

#endif
/*
namespace DebuggingConsoleDefinition
{
	using namespace Window_API;

	static int   Game_Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
	static int   Game_Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
	static char* Game_Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
	static void  Game_Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }


	class DebuggingConsole
	{
		public:
			DebuggingConsole();
			DebuggingConsole(bool trueConstructor);
			~DebuggingConsole();

			bool showself;
			char InputBuf[256]; // text input buffer;
			std::vector<std::string> Items;
			std::vector<std::string> Commands;
			std::vector<std::string> History;
			int history_pos;
			bool AutoScroll;
			bool ScrollToBottom;
			ImGuiTextFilter Filter;

			void cleanConsole();
			void addLog(const char* fmt, ...);
			void drawConsole(const char* title, bool* p_open);
			static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
			int TextEditCallback(ImGuiInputTextCallbackData* data);
			void ExecCommand(const char* command_line);

	};


	extern DebuggingConsole console;

}
*/