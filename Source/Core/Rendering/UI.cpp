#include "UI.h"

#include <algorithm>

#include "Camera.h"
#include "Core/HAL/PlatformMemory.h"
#include "URenderer.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"


void UI::Initialize(HWND hWnd, const URenderer& Renderer)
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
        ImGui::Text(
            "Memory Uses: %llubyte, Count: %llu",
            FPlatformMemory::GetTotalAllocationBytes(),
            FPlatformMemory::GetTotalAllocationCount()
        );
        
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

        ImGui::Text("Camera");
        
        FCamera& camera = FCamera::Get();
        
        bool IsOrthogonal;
        if (ImGui::Checkbox("Orthogonal", &IsOrthogonal))
        {
            if (IsOrthogonal)
            {
                camera.ProjectionMode = ECameraProjectionMode::Orthographic;   
            }
            else
            {
                camera.ProjectionMode = ECameraProjectionMode::Perspective;
            }
        }

        float FOV = camera.GetFieldOfView();
        if (ImGui::InputFloat("FOV", &FOV, 0))
        {
            FOV = std::clamp(FOV, 0.01f, 179.99f);
            camera.SetFieldOfVew(FOV);
        }

        float NearFar[2] = {camera.GetNear(), camera.GetFar()};
        if (ImGui::InputFloat2("Near, Far", NearFar))
        {
            NearFar[0] = max(0.01f, NearFar[0]);
            NearFar[1] = max(0.01f, NearFar[1]);
            
            if (NearFar[0] < NearFar[1])
            {
                camera.SetNear(NearFar[0]);
                camera.SetFar(NearFar[1]);
            }
            else
            {
                if (abs(NearFar[0] - camera.GetNear()) < 0.00001f)
                {
                    camera.SetFar(NearFar[0] + 0.01f);
                }
                else if (abs(NearFar[1] - camera.GetFar()) < 0.00001f)
                {
                    camera.SetNear(NearFar[1] - 0.01f);
                }
            }
        }
        
        float CameraLocation[] = {camera.GetPosition().X, camera.GetPosition().Y, camera.GetPosition().Z};
        if (ImGui::InputFloat3("Camera Location", CameraLocation))
        {
            camera.SetPosition(CameraLocation[0], CameraLocation[1], CameraLocation[2]);
        }

        float CameraRotation[] = {camera.GetRotation().X, camera.GetRotation().Y, camera.GetRotation().Z};
        if (ImGui::InputFloat3("Camera Rotation", CameraRotation))
        {
            camera.SetRotation(CameraRotation[0], CameraRotation[1], CameraRotation[2]);
        }

        FVector Forward = camera.GetForward();
        FVector Up = camera.GetUp();
        FVector Right = camera.GetRight();
        
        ImGui::Text("Camera Forward: (%.2f %.2f %.2f)", Forward.X, Forward.Y, Forward.Z);
        ImGui::Text("Camera Up: (%.2f %.2f %.2f)", Up.X, Up.Y, Up.Z);
        ImGui::Text("Camera Right: (%.2f %.2f %.2f)", Right.X, Right.Y, Right.Z);

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