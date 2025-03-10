#pragma once
#define _TCHAR_DEFINED
#include <Windows.h>
#include "ImGui/imgui.h"


class AActor;
class URenderer;

class UI
{
public:
    int currentItem = 0;
    int NumOfSpawn = 0;
	bool bIsInitialized = false;
    AActor* selectedActor = nullptr;
    
    void Initialize(HWND hWnd, const class URenderer& Renderer, UINT ScreenWidth, UINT ScreenHeight);
    void Update();
    void Shutdown();

	void OnUpdateWindowSize(UINT InScreenWidth, UINT InScreenHeight);

public:// UIWindows
    void RenderControlPanel();
	void RenderMemoryUsage();
    void RenderPrimitiveSelection();
    void RenderCameraSettings();
    void RenderPropertyWindow();


    bool bIsConsoleOpen = true;

    ImVec2 ScreenSize;
};
