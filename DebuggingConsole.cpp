#include "DebuggingConsole.hpp"

#include <sstream>

namespace DebugConsoleDefinition
{
	DebugConsole debug;
}

using namespace DebugConsoleDefinition;

// Don't ask me about this code. I don't even understand it.

struct DebugConsole::Impl
{
	char                  InputBuf[256];
	ImVector<char*>       Items;
	ImVector<const char*> Commands;
	ImVector<char*>       History;
	int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
	ImGuiTextFilter       Filter;
	bool                  AutoScroll;
	bool                  ScrollToBottom;

	// dear god forgive me
};

void DebugConsoleDefinition::DebugConsole::implementDebugConsole()
{
	self = new DebugConsole::Impl;
	self->Commands.push_back("Help");
	self->Commands.push_back("History");
	self->Commands.push_back("Clear");
	self->Commands.push_back("Classify");
	self->Commands.push_back("showme");
	self->AutoScroll = true;
	self->ScrollToBottom = false;

	for (int i = 0; i < 256; i++)
	{
		self->InputBuf[i] = 0;
	}
	say "Implemented Debug Console" done;
}

DebugConsoleDefinition::DebugConsole::DebugConsole()
{
}

DebugConsoleDefinition::DebugConsole::DebugConsole(bool trueConstructor)
{
	implementDebugConsole();
}

DebugConsoleDefinition::DebugConsole::~DebugConsole()
{
}
// the more important function - should probably not look at the others
void DebugConsoleDefinition::DebugConsole::ExecCommand(const char* command_line)
{
	std::string messagevar = command_line;
	std::string hold;
	std::istringstream ss(messagevar);
	std::vector<std::string> strvec;
	#define ConsoleMatch(pos, strmessage) strvec[(pos)] == (strmessage)


	while (ss >> hold)
	{
		strvec.push_back(hold);
	}
	forall(strs, strvec)
	{
		say strs done;
	}



	AddLog("GCO <-: %s\n", command_line);

	// Insert into history. First find match and delete it so it can be pushed to the back.
	// This isn't trying to be smart or optimal.
	self->HistoryPos = -1;
	for (int i = self->History.Size - 1; i >= 0; i--)
		if (Game_Stricmp(self->History[i], command_line) == 0)
		{
			free(self->History[i]);
			self->History.erase(self->History.begin() + i);
			break;
		}
	self->History.push_back(Game_Strdup(command_line));


	// Process command
	if (Game_Stricmp(command_line, "CLEAR") == 0 || Game_Stricmp(command_line, "CLS") == 0)
	{
		CleanConsole();
	}
	else if (Game_Stricmp(command_line, "HELP") == 0)
	{
		AddLog("Commands:");
		for (int i = 0; i < self->Commands.Size; i++)
			AddLog("- %s", self->Commands[i]);
	}
	else if (Game_Stricmp(command_line, "HISTORY") == 0)
	{
		int first = self->History.Size - 10;
		for (int i = first > 0 ? first : 0; i < self->History.Size; i++)
			AddLog("%3d: %s\n", i, self->History[i]);
	}
	else if (messagevar == "EasterEgg")
	{
		AddLog("GCO:-> Eat shit.");
	}
	else if(ConsoleMatch(0, "showme"))
	{
		if (strvec.size() == 1)
		{
			AddLog("GCO:-> Show you what? Usage: 'date', 'time', 'stats', 'total memory in use'");
		}

	}
	else if (ConsoleMatch(0, "exit"))
	{
		exit(0);
	}

	else
	{
		AddLog("GCO:-> Unknown Command: '%s'\n", command_line);
	}

	// On command input, we scroll to bottom even if AutoScroll==false
	self->ScrollToBottom = true;
}


void DebugConsoleDefinition::DebugConsole::AddLog(const char* fmt, ...)
{
	// FIXME-OPT
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);
	self->Items.push_back(Game_Strdup(buf));
}

void DebugConsoleDefinition::DebugConsole::CleanConsole()
{
	for (int i = 0; i < self->Items.Size; i++)
		free(self->Items[i]);
	self->Items.clear();
}

void DebugConsoleDefinition::DebugConsole::Draw(bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(title, p_open))
	{
		ImGui::End();
		return;
	}

	// As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
	// So e.g. IsItemHovered() will return true when hovering the title bar.
	// Here we create a context menu only available from the title bar.
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Close Console"))
			*p_open = false;
		ImGui::EndPopup();
	}

	ImGui::TextWrapped("Enter 'HELP' for help.");

	// TODO: display items starting from the bottom

	if (ImGui::SmallButton("Add Debug Text")) { AddLog("%d some text", self->Items.Size); AddLog("some more text"); AddLog("display very important message here!"); }
	ImGui::SameLine();
	if (ImGui::SmallButton("Add Debug Error")) { AddLog("[error] something went wrong"); }
	ImGui::SameLine();
	if (ImGui::SmallButton("Clear")) { CleanConsole(); }
	ImGui::SameLine();
	bool copy_to_clipboard = ImGui::SmallButton("Copy");
	//static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

	ImGui::Separator();

	// Options menu
	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Auto-scroll", &self->AutoScroll);
		ImGui::EndPopup();
	}

	// Options, Filter
	if (ImGui::Button("Options"))
		ImGui::OpenPopup("Options");
	ImGui::SameLine();
	self->Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
	ImGui::Separator();

	// Reserve enough left-over height for 1 separator + 1 input text
	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::Selectable("Clear")) CleanConsole();
		ImGui::EndPopup();
	}

	// Display every line as a separate entry so we can change their color or add custom widgets.
	// If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
	// NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
	// to only process visible items. The clipper will automatically measure the height of your first item and then
	// "seek" to display only items in the visible area.
	// To use the clipper we can replace your standard loop:
	//      for (int i = 0; i < Items.Size; i++)
	//   With:
	//      ImGuiListClipper clipper;
	//      clipper.Begin(Items.Size);
	//      while (clipper.Step())
	//         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
	// - That your items are evenly spaced (same height)
	// - That you have cheap random access to your elements (you can access them given their index,
	//   without processing all the ones before)
	// You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
	// We would need random-access on the post-filtered list.
	// A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
	// or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
	// and appending newly elements as they are inserted. This is left as a task to the user until we can manage
	// to improve this example code!
	// If your items are of variable height:
	// - Split them into same height items would be simpler and facilitate random-seeking into your list.
	// - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
	if (copy_to_clipboard)
		ImGui::LogToClipboard();
	for (int i = 0; i < self->Items.Size; i++)
	{
		const char* item = self->Items[i];
		if (!self->Filter.PassFilter(item))
			continue;

		// Normally you would store more information in your item than just a string.
		// (e.g. make Items[] an array of structure, store color/type etc.)
		ImVec4 color;
		bool has_color = false;
		if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
		else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
		if (has_color)
			ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::TextUnformatted(item);
		if (has_color)
			ImGui::PopStyleColor();
	}
	if (copy_to_clipboard)
		ImGui::LogFinish();

	if (self->ScrollToBottom || (self->AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
		ImGui::SetScrollHereY(1.0f);
	self->ScrollToBottom = false;

	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::Separator();

	// Command-line
	bool reclaim_focus = false;
	ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
	if (ImGui::InputText("Input", self->InputBuf, IM_ARRAYSIZE(self->InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
	{
		char* s = self->InputBuf;
		Game_Strtrim(s);
		if (s[0])
			ExecCommand(s);
		strcpy(s, "");
		reclaim_focus = true;
	}

	// Auto-focus on window apparition
	ImGui::SetItemDefaultFocus();
	if (reclaim_focus)
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

	ImGui::End();
}

// you don't want to know why this works.
int DebugConsoleDefinition::DebugConsole::TextEditCallbackStub(ImGuiInputTextCallbackData* data)
{
	DebugConsole* console = (DebugConsole*)data->UserData;
	return console->TextEditCallback(data);
}

int DebugConsoleDefinition::DebugConsole::TextEditCallback(ImGuiInputTextCallbackData* data)
{
	//AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
	switch (data->EventFlag)
	{
		case ImGuiInputTextFlags_CallbackCompletion:
		{
			// Example of TEXT COMPLETION

			// Locate beginning of current word
			const char* word_end = data->Buf + data->CursorPos;
			const char* word_start = word_end;
			while (word_start > data->Buf)
			{
				const char c = word_start[-1];
				if (c == ' ' || c == '\t' || c == ',' || c == ';')
					break;
				word_start--;
			}

			// Build a list of candidates
			ImVector<const char*> candidates;
			for (int i = 0; i < self->Commands.Size; i++)
				if (Game_Strnicmp(self->Commands[i], word_start, (int)(word_end - word_start)) == 0)
					candidates.push_back(self->Commands[i]);

			if (candidates.Size == 0)
			{
				// No match
				AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
			}
			else if (candidates.Size == 1)
			{
				// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
				data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
				data->InsertChars(data->CursorPos, candidates[0]);
				data->InsertChars(data->CursorPos, " ");
			}
			else
			{
				// Multiple matches. Complete as much as we can..
				// So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
				int match_len = (int)(word_end - word_start);
				for (;;)
				{
					int c = 0;
					bool all_candidates_matches = true;
					for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
						if (i == 0)
							c = toupper(candidates[i][match_len]);
						else if (c == 0 || c != toupper(candidates[i][match_len]))
							all_candidates_matches = false;
					if (!all_candidates_matches)
						break;
					match_len++;
				}

				if (match_len > 0)
				{
					data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
					data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
				}

				// List matches
				AddLog("Possible matches:\n");
				for (int i = 0; i < candidates.Size; i++)
					AddLog("- %s\n", candidates[i]);
			}

			break;
		}
		case ImGuiInputTextFlags_CallbackHistory:
		{
			// Example of HISTORY
			const int prev_history_pos = self->HistoryPos;
			if (data->EventKey == ImGuiKey_UpArrow)
			{
				if (self->HistoryPos == -1)
					self->HistoryPos = self->History.Size - 1;
				else if (self->HistoryPos > 0)
					self->HistoryPos--;
			}
			else if (data->EventKey == ImGuiKey_DownArrow)
			{
				if (self->HistoryPos != -1)
					if (++self->HistoryPos >= self->History.Size)
						self->HistoryPos = -1;
			}

			// A better implementation would preserve the data on the current input line along with cursor position.
			if (prev_history_pos != self->HistoryPos)
			{
				const char* history_str = (self->HistoryPos >= 0) ? self->History[self->HistoryPos] : "";
				data->DeleteChars(0, data->BufTextLen);
				data->InsertChars(0, history_str);
			}
		}
	}
	return 0;
}



































/*
namespace DebuggingConsoleDefinition
{
	DebuggingConsole console; // globalized
}
	 

using namespace DebuggingConsoleDefinition;
using std::stringstream;

DebuggingConsoleDefinition::DebuggingConsole::DebuggingConsole()
{
}

DebuggingConsoleDefinition::DebuggingConsole::DebuggingConsole(bool trueConstructor)
{
	Commands.push_back("Help");
	Commands.push_back("History");
	Commands.push_back("Clear");
	Commands.push_back("Classify");
	Commands.push_back("showme");
	AutoScroll = true;
	ScrollToBottom = false;
	// 0 out the draw buffer
	for (int i = 0; i < 256; i++)
	{
		InputBuf[i] = 0;
	}

	say "Console Inititalized" done;
}

DebuggingConsoleDefinition::DebuggingConsole::~DebuggingConsole()
{

}

void DebuggingConsoleDefinition::DebuggingConsole::cleanConsole()
{
	const int itemSize = Items.size();
	for (int i = 0; i < itemSize; i++)
	{
		Items[i].clear();
	}

	Items.clear();
}

void DebuggingConsoleDefinition::DebuggingConsole::addLog(const char* fmt, ...)
{
	// FIXME-OPT
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);
	Items.push_back(Game_Strdup(buf));

}

void DebuggingConsoleDefinition::DebuggingConsole::drawConsole(const char* title, bool* p_open)
{
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(title, p_open))
	{
		ImGui::End();
		return;
	}

	// As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
	// So e.g. IsItemHovered() will return true when hovering the title bar.
	// Here we create a context menu only available from the title bar.
	if (ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Close Console"))
			*p_open = false;
		ImGui::EndPopup();
	}
	ImGui::TextWrapped("Enter 'HELP' for help.");

	// TODO: display items starting from the bottom

	if (ImGui::SmallButton("Add Debug Text")) { addLog("%d some text", Items.size()); addLog("some more text"); addLog("display very important message here!"); }
	ImGui::SameLine();
	if (ImGui::SmallButton("Add Debug Error")) { addLog("[error] something went wrong"); }
	ImGui::SameLine();
	if (ImGui::SmallButton("Clear")) { cleanConsole(); }
	ImGui::SameLine();
	bool copy_to_clipboard = ImGui::SmallButton("Copy");
	//static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

	ImGui::Separator();

	// Options menu
	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Auto-scroll", &AutoScroll);
		ImGui::EndPopup();
	}

	// Options, Filter
	if (ImGui::Button("Options"))
		ImGui::OpenPopup("Options");
	ImGui::SameLine();
	Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
	ImGui::Separator();

	// Reserve enough left-over height for 1 separator + 1 input text
	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::Selectable("Clear")) cleanConsole();
		ImGui::EndPopup();
	}

	// Display every line as a separate entry so we can change their color or add custom widgets.
	// If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
	// NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
	// to only process visible items. The clipper will automatically measure the height of your first item and then
	// "seek" to display only items in the visible area.
	// To use the clipper we can replace your standard loop:
	//      for (int i = 0; i < Items.Size; i++)
	//   With:
	//      ImGuiListClipper clipper;
	//      clipper.Begin(Items.Size);
	//      while (clipper.Step())
	//         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
	// - That your items are evenly spaced (same height)
	// - That you have cheap random access to your elements (you can access them given their index,
	//   without processing all the ones before)
	// You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
	// We would need random-access on the post-filtered list.
	// A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
	// or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
	// and appending newly elements as they are inserted. This is left as a task to the user until we can manage
	// to improve this example code!
	// If your items are of variable height:
	// - Split them into same height items would be simpler and facilitate random-seeking into your list.
	// - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
	if (copy_to_clipboard)
		ImGui::LogToClipboard();
	const int itemSize = Items.size();
	for (int i = 0; i < itemSize; i++)
	{
		const char* item = Items[i].c_str();
		if (Filter.PassFilter(item))
			continue;

		// Normally you would store more information in your item than just a string.
		// (e.g. make Items[] an array of structure, store color/type etc.)
		ImVec4 color;
		bool has_color = false;
		if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
		else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
		if (has_color)
			ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::TextUnformatted(item);
		if (has_color)
			ImGui::PopStyleColor();
	}
	if (copy_to_clipboard)
		ImGui::LogFinish();

	if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
		ImGui::SetScrollHereY(1.0f);
	ScrollToBottom = false;

	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::Separator();

	// Command-line
	bool reclaim_focus = false;
	ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
	if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
	{
		char* s = InputBuf;
		Game_Strtrim(s);
		if (s[0])
			ExecCommand(s);
		strcpy(s, "");
		reclaim_focus = true;
	}

	// Auto-focus on window apparition
	ImGui::SetItemDefaultFocus();
	if (reclaim_focus)
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

	ImGui::End();
}

// I have no explanation at all what this is doing.
int DebuggingConsoleDefinition::DebuggingConsole::TextEditCallbackStub(ImGuiInputTextCallbackData* data)
{

	DebuggingConsole* cnsole = (DebuggingConsole*)data->UserData;
	return cnsole->TextEditCallback(data);

}

int DebuggingConsoleDefinition::DebuggingConsole::TextEditCallback(ImGuiInputTextCallbackData* data)
{
	switch (data->EventFlag)
	{
		case ImGuiInputTextFlags_CallbackCompletion:
		{
			// Example of TEXT COMPLETION

			// Locate beginning of current word
			const char* word_end = data->Buf + data->CursorPos;
			const char* word_start = word_end;
			while (word_start > data->Buf)
			{
				const char c = word_start[-1];
				if (c == ' ' || c == '\t' || c == ',' || c == ';')
					break;
				word_start--;
			}

			// Build a list of candidates
			ImVector<const char*> candidates;
			const int commandsSize = Commands.size();
			for (int i = 0; i < commandsSize; i++)
				if (Game_Strnicmp(Commands[i].c_str(), word_start, (int)(word_end - word_start)) == 0)
					candidates.push_back(Commands[i].c_str());

			if (candidates.Size == 0)
			{
				// No match
				addLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
			}
			else if (candidates.Size == 1)
			{
				// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
				data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
				data->InsertChars(data->CursorPos, candidates[0]);
				data->InsertChars(data->CursorPos, " ");
			}
			else
			{
				// Multiple matches. Complete as much as we can..
				// So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
				int match_len = (int)(word_end - word_start);
				for (;;)
				{
					int c = 0;
					bool all_candidates_matches = true;
					for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
						if (i == 0)
							c = toupper(candidates[i][match_len]);
						else if (c == 0 || c != toupper(candidates[i][match_len]))
							all_candidates_matches = false;
					if (!all_candidates_matches)
						break;
					match_len++;
				}

				if (match_len > 0)
				{
					data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
					data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
				}

				// List matches
				addLog("Possible matches:\n");
				for (int i = 0; i < candidates.Size; i++)
					addLog("- %s\n", candidates[i]);
			}

			break;
		}
		case ImGuiInputTextFlags_CallbackHistory:
		{
			// Example of HISTORY
			const int prev_history_pos = this->history_pos;
			if (data->EventKey == ImGuiKey_UpArrow)
			{
				if (history_pos == -1)
					history_pos = History.size() - 1;
				else if (history_pos > 0)
					history_pos--;
			}
			else if (data->EventKey == ImGuiKey_DownArrow)
			{
				if (history_pos != -1)
					if (++history_pos >= History.size())
						history_pos = -1;
			}

			// A better implementation would preserve the data on the current input line along with cursor position.
			if (prev_history_pos != history_pos)
			{
				const char* history_str = (history_pos >= 0) ? History[history_pos].c_str() : "";
				data->DeleteChars(0, data->BufTextLen);
				data->InsertChars(0, history_str);
			}
		}
	}
	return 0;

}

void DebuggingConsoleDefinition::DebuggingConsole::ExecCommand(const char* command_line)
{
	std::string messagevar = command_line;
	std::string hold;
	std::istringstream ss(messagevar);

	std::vector<std::string> strvec;

#define ConsoleMatch(pos, strmessage) strvec[(pos)] == (strmessage)

	while (ss >> hold)
	{
		strvec.push_back(hold);
	}
	forall(strs, strvec)
	{
		say strs done;
	}



	addLog("GCO <-: %s\n", command_line);

	// Insert into history. First find match and delete it so it can be pushed to the back.
	// This isn't trying to be smart or optimal.
	this->history_pos = -1;
	for (int i = History.size() - 1; i >= 0; i--)
		if (Game_Stricmp(History[i].c_str(), command_line) == 0)
		{

			History[i].clear();
			History.erase(History.begin() + i);
			break;
		}
	History.push_back(Game_Strdup(command_line));


	// Process command
	if (Game_Stricmp(command_line, "CLEAR") == 0 || Game_Stricmp(command_line, "CLS") == 0)
	{
		cleanConsole();
	}
	else if (Game_Stricmp(command_line, "HELP") == 0)
	{
		addLog("Commands:");
		const int commandSize = Commands.size();
		for (int i = 0; i < commandSize; i++)
			addLog("- %s", Commands[i].c_str());
	}
	else if (Game_Stricmp(command_line, "HISTORY") == 0)
	{
		int first = History.size() - 10;
		const int historySize = History.size();
		for (int i = first > 0 ? first : 0; i < historySize; i++)
			addLog("%3d: %s\n", i, History[i].c_str());
	}
	else if (messagevar == "EasterEgg")
	{
		addLog("GCO:-> Eat shit.");
	}
	eif(ConsoleMatch(0, "showme"))
	{
		if (strvec.size() == 1)
		{
			addLog("GCO:-> Show you what? Usage: 'date', 'time', 'stats', 'total memory in use'");
		}
	}
	eif(strvec[0] == "showme")
	{
		
		exit(0);
	}

	else
	{
		addLog("GCO:-> Unknown Command: '%s'\n", command_line);
	}

	// On command input, we scroll to bottom even if AutoScroll==false
	ScrollToBottom = true;
}
*/
