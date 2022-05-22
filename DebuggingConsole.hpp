#ifndef DebuggingConsole_HPP
#define DebuggingConsole_HPP

#include "Window_API.hpp"

namespace DebuggingConsoleDefinition
{
	using namespace Window_API;

	static int   Game_Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
	static int   Game_Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
	static char* Game_Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
	static void  Game_Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

	// this implementation of a debugging console is based off an old design of David. It's based partially on ImGUI's demo but makes multiple changes to use std data structures
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

#endif
