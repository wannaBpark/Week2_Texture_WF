#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <Windows.h>
#include <d3d11.h>

#include "Core/Rendering/UI.h"
#include "ImGui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Core/Math/Vector.h"
#include "Primitive/PrimitiveVertices.h"
#include "Core/Engine.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	UEngine& Engine = UEngine::Get();
	Engine.Initialize(hInstance, L"Jungle Engine", L"JungleWindow", 1280, 720);

	Engine.Run();

	Engine.Shutdown();

    return 0;
}
