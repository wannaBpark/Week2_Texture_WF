#include "Engine.h"

#include <iostream>
#include "Object/FObjectFactory.h"
#include "Object/USceneComponent.h"
#include "Object/World/World.h"
#include "Debug/DebugConsole.h"

// ImGui WndProc 정의
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT UEngine::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // ImGui의 메시지를 처리
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    {
        return true;
    }

    switch (uMsg)
    {
        // 창이 제거될 때 (창 닫기, Alt+F4 등)
    case WM_DESTROY:
        PostQuitMessage(0); // 프로그램 종료
        break;

    case WM_KEYDOWN:
        break;

    case WM_KEYUP:
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

void UEngine::Initialize(
    HINSTANCE hInstance, const WCHAR* InWindowTitle, const WCHAR* InWindowClassName, int InScreenWidth,
    int InScreenHeight,
    EScreenMode InScreenMode
)
{
    WindowInstance = hInstance;
    WindowTitle = InWindowTitle;
    WindowClassName = InWindowClassName;
    ScreenMode = InScreenMode;
    ScreenWidth = InScreenWidth;
    ScreenHeight = InScreenHeight;

    InitWindow(InScreenWidth, InScreenWidth);
    InitWorld();
    InitRenderer();

	UE_LOG("Engine Initialized!");
}

void UEngine::Run()
{
    // FPS 제한
    constexpr int TargetFPS = 750;
    constexpr double TargetDeltaTime = 1000.0f / TargetFPS; // 1 FPS의 목표 시간 (ms)

    // 고성능 타이머 초기화
    LARGE_INTEGER Frequency;
    QueryPerformanceFrequency(&Frequency);

    LARGE_INTEGER StartTime;
    QueryPerformanceCounter(&StartTime);


    IsRunning = true;
    while (IsRunning)
    {
        // DeltaTime 계산 (초 단위)
        const LARGE_INTEGER EndTime = StartTime;
        QueryPerformanceCounter(&StartTime);

        const float DeltaTime =
            static_cast<float>(StartTime.QuadPart - EndTime.QuadPart) / static_cast<float>(Frequency.QuadPart);


        // 메시지(이벤트) 처리
        MSG Msg;
        while (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 키 입력 메시지를 번역
            TranslateMessage(&Msg);

            // 메시지를 등록한 Proc에 전달
            DispatchMessage(&Msg);

            if (Msg.message == WM_QUIT)
            {
                IsRunning = false;
                break;
            }
        }
		// Renderer Update
        Renderer->Prepare();
        Renderer->PrepareShader();

		// World Update
		if (World)
		{
			World->Tick(DeltaTime);
		}

		// ui Update
        ui.Update();

        Renderer->SwapBuffer();

        // FPS 제한
        double ElapsedTime;
        do
        {
            Sleep(0);

            LARGE_INTEGER CurrentTime;
            QueryPerformanceCounter(&CurrentTime);

            ElapsedTime = static_cast<double>(CurrentTime.QuadPart - StartTime.QuadPart) * 1000.0 / static_cast<double>(Frequency.QuadPart);
        } while (ElapsedTime < TargetDeltaTime);
    }
}

void UEngine::Shutdown()
{
    ShutdownWindow();
}


void UEngine::InitWindow(int InScreenWidth, int InScreenHeight)
{
    // 윈도우 클래스 등록
    WNDCLASSW wnd_class{};
    wnd_class.lpfnWndProc = WndProc;
    wnd_class.hInstance = WindowInstance;
    wnd_class.lpszClassName = WindowClassName;
    RegisterClassW(&wnd_class);

    // Window Handle 생성
    WindowHandle = CreateWindowExW(
        0, WindowClassName, WindowTitle,
        WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        InScreenWidth, InScreenHeight,
        nullptr, nullptr, WindowInstance, nullptr
    );

    // TODO: 전체화면 구현
    if (ScreenMode != EScreenMode::Windowed)
    {
        std::cout << "not implement Fullscreen and Borderless mode." << '\n';
    }

    // 윈도우 포커싱
    ShowWindow(WindowHandle, SW_SHOW);
    SetForegroundWindow(WindowHandle);
    SetFocus(WindowHandle);
}

void UEngine::InitRenderer()
{
	// 렌더러 초기화
	Renderer = std::make_unique<URenderer>();
	Renderer->Create(WindowHandle);
	Renderer->CreateShader();
	Renderer->CreateConstantBuffer();

	ui.Initialize(WindowHandle, *Renderer);
}

void UEngine::InitWorld()
{
    World = FObjectFactory::ConstructObject<UWorld>();

	// !TODO : Load World

	World->BeginPlay();
}

void UEngine::ShutdownWindow()
{
    DestroyWindow(WindowHandle);
    WindowHandle = nullptr;

    UnregisterClassW(WindowClassName, WindowInstance);
    WindowInstance = nullptr;

	ui.Shutdown();
}
