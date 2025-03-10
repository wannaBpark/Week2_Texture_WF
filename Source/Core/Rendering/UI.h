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

private:
	ImVec2 ResizeToScreen(const ImVec2& vec2) const;

    ImVec2 GetRatio() const;

	bool bIsConsoleOpen = true;
	
    ImVec2 ScreenSize;
	ImVec2 InitialScreenSize;
};
