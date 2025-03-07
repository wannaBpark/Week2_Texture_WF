#include "UI.h"

#include <Windows.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"


void UI::Initialize(HWND hWnd, URenderer Renderer)
{
    // ImGui 초기화
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // ImGui Backend 초기화
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(Renderer.GetDevice(), Renderer.GetDeviceContext());
}

void UI::Update()
{
    // ImGui Frame 생성
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (ImGui::Begin("Jungle Control Panel"))
    {
        ImGui::Text("Hello, Jungle World!");
        ImGui::Text("FPS: %.3f (what is that ms)", ImGui::GetIO().Framerate);

        ImGui::Separator();
        
        const char* items[] = { "Sphere", "Cube"};
        int currentItem = 1;
        
        ImGui::Combo("Primitive", &currentItem, items, IM_ARRAYSIZE(items));

        if (ImGui::Button("Spawn"))
        {
            
        }
        ImGui::SameLine();
        int NumOfSpawn;
        ImGui::InputInt("Number of spawn", &NumOfSpawn, 0);


        ImGui::Separator();

        char test[100] = "1";
        ImGui::InputText("Scene Name", test, 100);
        if (ImGui::Button("New Scene"))
        {
            
        }
        if (ImGui::Button("Save Scene"))
        {
            
        }
        if (ImGui::Button("Load Scene"))
        {
            
        }
        ImGui::Separator();

        bool orthogonal;
        ImGui::Checkbox("Orthogonal", &orthogonal);

        float Fov;
        if (ImGui::InputFloat("FOV", &Fov, 0))
        {
            
        }               

        float CameraLocation[3];
        if (ImGui::InputFloat3("Camera Location", CameraLocation))
        {
            
        }

        float CameraRotation[3];
        if (ImGui::InputFloat3("Camera Rotation", CameraRotation))
        {
            
        }
        
        ImGui::Text("Memory: what");

        ImGui::End();
    }

    if (ImGui::Begin("Jungle Property Window"))
    {
        float a[3];
        ImGui::InputFloat3("Translation", a);
        ImGui::InputFloat3("Rotation", a);
        ImGui::InputFloat3("Scale", a);
        ImGui::End();
    }

    if (ImGui::Begin("Console Window"))
    {
        ImGui::Text("completion (TAB Key), history (Up/Down).");
        if (ImGui::Button("Add Debug Text"))
        {
        
        }
        ImGui::SameLine();
        if (ImGui::Button("Add Debug Error"))
        {
        
        }

        ImGui::SameLine();
        if (ImGui::Button("Clear"))
        {
        
        }
        ImGui::SameLine();
        if (ImGui::Button("Copy"))
        {
        
        }
        ImGui::End();
    }
    
    // ImGui 렌더링
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UI::Shutdown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
