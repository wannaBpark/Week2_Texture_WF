
#include "Debug/DebugConsole.h"
#include <cstdarg>
#include <algorithm>

std::vector<std::string> Debug::items;

void Debug::ShowConsole(bool* bOpen)
{
    static char inputBuf[256] = "";
    static std::vector<std::string> history;
    static int historyPos = -1;
    bool reclaimFocus = false;

    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Console", bOpen))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true, ImGuiWindowFlags_HorizontalScrollbar))
    {
        for (const auto& Item : items)
            ImGui::TextUnformatted(Item.c_str());

        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();

    if (ImGui::InputText("Input", inputBuf, IM_ARRAYSIZE(inputBuf),
        ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackHistory,
        [](ImGuiInputTextCallbackData* data) -> int
        {
            if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory)
            {
                if (history.empty()) return 0;
                historyPos += (data->EventKey == ImGuiKey_UpArrow) ? -1 : 1;
                historyPos = std::clamp(historyPos, 0, (int)history.size() - 1);

                std::string& historyCommand = history[historyPos];
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, historyCommand.c_str());
            }
            return 0;
        }))
    {
        std::string inputStr = inputBuf;
        if (!inputStr.empty())
        {
            items.push_back("> " + inputStr);
            history.push_back(inputStr);
            historyPos = (int)history.size();
            ProcessCommand(inputStr, items);
        }
        inputBuf[0] = '\0';
        reclaimFocus = true;
    }

    if (reclaimFocus)
        ImGui::SetKeyboardFocusHere(-1);
    ImGui::End();
}

void Debug::ProcessCommand(const std::string& command, std::vector<std::string>& log)
{
    log.push_back("Executing: " + command);

    if (command == "clear")
    {
        log.clear();
    }
    else if (command == "help")
    {
        log.push_back("Available commands:");
        log.push_back("- clear: Clears the console.");
        log.push_back("- help: Shows this help message.");
    }
    else
    {
        log.push_back("Unknown command: " + command);
    }
}

void Debug::Log(const char* format, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    items.emplace_back(buffer);
}