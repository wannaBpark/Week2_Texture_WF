#pragma once
#include <vector>
#include <string>
#include "ImGui/imgui.h"

#define UE_LOG(format, ...) Debug::Log(format, ##__VA_ARGS__)


static class Debug
{
    friend class Debug;
    
    static std::vector<std::string> items; // 출력 로그

public:
    static void ShowConsole(bool bWasWindowSizeUpdated, ImVec2 PreRatio, ImVec2 CurRatio);
    static void ProcessCommand(const std::string& command, std::vector<std::string>& log);
    static void Log(const char* format, ...);
    static ImVec2 ResizeToScreen(const ImVec2& vec2, ImVec2 PreRatio, ImVec2 CurRatio);
};