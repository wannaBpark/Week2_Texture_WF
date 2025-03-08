#pragma once

#define _TCHAR_DEFINED  // TCHAR 재정의 에러 때문
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>

#include "HAL/PlatformType.h"
#include "Rendering/URenderer.h"
#include "Rendering/UI.h"
#include "AbstractClass/Singleton.h"

enum class EScreenMode : uint8
{
    Windowed,    // 창 모드
    Fullscreen,  // 전체화면 모드
    Borderless,  // 테두리 없는 창 모드
};

class UEngine : public TSingleton<UEngine>
{
public:
    // 각종 윈도우 관련 메시지(이벤트)를 처리하는 함수
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /**
     * Application을 초기화 합니다.
     * @param hInstance 창 인스턴스
     * @param InWindowTitle 윈도우 창 이름
     * @param InWindowClassName 윈도우 클래스 이름
     * @param InScreenWidth 화면 너비
     * @param InScreenHeight 화면 높이
     * @param InScreenMode 창 모드
     * @return 초기화 여부
     */
    void Initialize(
        HINSTANCE hInstance, const WCHAR* InWindowTitle, const WCHAR* InWindowClassName, int InScreenWidth,
        int InScreenHeight, EScreenMode InScreenMode = EScreenMode::Windowed
    );
    void Run();

    /**
     * Application에서 사용한 자원을 정리합니다.
     */
    void Shutdown();

	class URenderer* GetRenderer() const { return Renderer.get(); }
	float GetScreenRatio() const { return static_cast<float>(ScreenWidth) / ScreenHeight; }

#ifdef _DEBUG
    void OpenDebugConsole() const;
    void CloseDebugConsole() const;
#endif

private:
    void InitWindow(int InScreenWidth, int InScreenHeight);
    void InitRenderer();
    void ShutdownWindow();

private:
    bool IsRunning = false;
    EScreenMode ScreenMode = EScreenMode::Windowed;

    const WCHAR* WindowTitle = nullptr;
    const WCHAR* WindowClassName = nullptr;
    HWND WindowHandle = nullptr;
    HINSTANCE WindowInstance = nullptr;

    int ScreenWidth = 0;
    int ScreenHeight = 0;

private:
	std::unique_ptr<URenderer> Renderer;

private:
	UI ui;
};
