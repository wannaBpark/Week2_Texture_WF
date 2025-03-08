#include "UI.h"

#include <algorithm>

#include "Camera.h"
#include "Core/HAL/PlatformMemory.h"
#include "URenderer.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Object/Actor/Actor.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"
#include "Object/FObjectFactory.h"


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

        const uint64 ContainerAllocByte = FPlatformMemory::GetAllocationBytes<EAT_Container>();
        const uint64 ContainerAllocCount = FPlatformMemory::GetAllocationCount<EAT_Container>();
        const uint64 ObjectAllocByte = FPlatformMemory::GetAllocationBytes<EAT_Object>();
        const uint64 ObjectAllocCount = FPlatformMemory::GetAllocationCount<EAT_Object>();
        ImGui::Text(
            "Container Memory Uses: %llubyte, Count: %llu",
            ContainerAllocByte,
            ContainerAllocCount
        );
        ImGui::Text(
            "Object Memory Uses: %llubyte, Count: %llu Objects",
            ObjectAllocByte,
            ObjectAllocCount
        );
        ImGui::Text(
            "Total Memory Uses: %llubyte, Count: %llu",
            ContainerAllocByte + ObjectAllocByte,
            ContainerAllocCount + ObjectAllocCount
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
            NearFar[0] = FMath::Max(0.01f, NearFar[0]);
            NearFar[1] = FMath::Max(0.01f, NearFar[1]);
            
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
        
        FVector CameraLocation = camera.GetPosition();
        if (ImGui::DragFloat3("Camera Location", reinterpret_cast<float*>(&CameraLocation), 0.1f))
        {
            camera.SetPosition(CameraLocation);
        }

        FVector CameraRotation = camera.GetRotation();
        if (ImGui::DragFloat3("Camera Rotation", reinterpret_cast<float*>(&CameraRotation), 0.1f))
        {
            camera.SetRotation(CameraRotation);
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

    //test
    if (ImGui::Button("Create Sphere Actor"))
    {
		AActor* Actor = FObjectFactory::ConstructActor<AActor>();
		Actor->AddComponent<USphereComp>();
		Actor->AddComponent<UCubeComp>();
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