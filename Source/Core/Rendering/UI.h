#pragma once
#define _TCHAR_DEFINED
#include <Windows.h>

class URenderer;

class UI
{
public:
    void Initialize(HWND hWnd, const URenderer& Renderer);
    void Update();
    void Shutdown();

    bool bIsConsoleOpen = true;
};
