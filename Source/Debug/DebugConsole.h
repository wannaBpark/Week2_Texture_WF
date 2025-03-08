#pragma once
#include <vector>
#include <string>
#include "ImGui/imgui.h"

#define UE_LOG(format, ...) Debug::Log(format, ##__VA_ARGS__)


static class Debug
{
    static std::vector<std::string> items; // 출력 로그

public:
    static void ShowConsole(bool* bOpen);
    static void ProcessCommand(const std::string& command, std::vector<std::string>& log);
    static void Log(const char* format, ...);
};