#include "UI.h"

#include <algorithm>

#include "Camera.h"
#include "URenderer.h"
#include "Core/HAL/PlatformMemory.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Object/Actor/Actor.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"
#include "Object/ObjectFactory.h"
#include "Debug/DebugConsole.h"
#include <Object/Actor/Sphere.h>
#include <Object/Actor/Cube.h>

#include "Static/FEditorManager.h"


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

        ImGui::Combo("Primitive", &currentItem, items, IM_ARRAYSIZE(items));

        if (ImGui::Button("Spawn"))
        {
            for (int i = 0 ;  i < NumOfSpawn; i++)
            {
                if (strcmp(items[currentItem], "Sphere") == 0)
                {
                    FObjectFactory::ConstructActor<ASphere>()->SetTransform(FTransform(FVector(rand() % 10, rand() % 10, rand() % 10), FVector(0, 0, 0), FVector(1, 1, 1)));
                }
                else if (strcmp(items[currentItem], "Cube") == 0)
                {
					FObjectFactory::ConstructActor<ACube>();
                }
                //else if (strcmp(items[currentItem], "Triangle") == 0)
                //{
                //    Actor->AddComponent<UTriangleComp>();   
                //}
            }
        }
        ImGui::SameLine();
        ImGui::InputInt("Number of spawn", &NumOfSpawn, 0);


        ImGui::Separator();

        UWorld* World = UEngine::Get().GetWorld();
        uint32 bufferSize = 100;
        char* SceneNameInput = new char[bufferSize];
        strcpy_s(SceneNameInput, bufferSize, *World->SceneName);
        // std::copy(World->SceneName.begin(), World->SceneName.end(), SceneNameInput);
        if (ImGui::InputText("Scene Name", SceneNameInput, bufferSize))
        {
             World->SceneName = SceneNameInput;
        }
        if (ImGui::Button("Save Scene"))
        {
            World->SaveWorld();   
        }
        if (ImGui::Button("Load Scene"))
        {
            World->LoadWorld(SceneNameInput);
        }
        ImGui::Separator();

        ImGui::Text("Camera");
        
        FCamera& Camera = FCamera::Get();

        bool IsOrthogonal;
        if (Camera.ProjectionMode == ECameraProjectionMode::Orthographic)
        {
            IsOrthogonal = true;
        }
        else if (Camera.ProjectionMode == ECameraProjectionMode::Perspective)
        {
            IsOrthogonal = false;
        }
        
        if (ImGui::Checkbox("Orthogonal", &IsOrthogonal))
        {
            if (IsOrthogonal)
            {
                Camera.ProjectionMode = ECameraProjectionMode::Orthographic;   
            }
            else
            {
                Camera.ProjectionMode = ECameraProjectionMode::Perspective;
            }
        }

        float FOV = Camera.GetFieldOfView();
        if (ImGui::DragFloat("FOV", &FOV, 0.1f))
        {
            FOV = std::clamp(FOV, 0.01f, 179.99f);
            Camera.SetFieldOfVew(FOV);
        }

        float NearFar[2] = {Camera.GetNear(), Camera.GetFar()};
        if (ImGui::DragFloat2("Near, Far", NearFar, 0.1f))
        {
            NearFar[0] = FMath::Max(0.01f, NearFar[0]);
            NearFar[1] = FMath::Max(0.01f, NearFar[1]);
            
            if (NearFar[0] < NearFar[1])
            {
                Camera.SetNear(NearFar[0]);
                Camera.SetFar(NearFar[1]);
            }
            else
            {
                if (abs(NearFar[0] - Camera.GetNear()) < 0.00001f)
                {
                    Camera.SetFar(NearFar[0] + 0.01f);
                }
                else if (abs(NearFar[1] - Camera.GetFar()) < 0.00001f)
                {
                    Camera.SetNear(NearFar[1] - 0.01f);
                }
            }
        }
        
        float CameraLocation[] = {Camera.GetTransform().GetPosition().X, Camera.GetTransform().GetPosition().Y, Camera.GetTransform().GetPosition().Z};
        if (ImGui::InputFloat3("Camera Location", CameraLocation))
        {
            Camera.GetTransform().SetPosition(CameraLocation[0], CameraLocation[1], CameraLocation[2]);
        }

        float CameraRotation[] = {Camera.GetTransform().GetRotation().Y, Camera.GetTransform().GetRotation().Z};
        if (ImGui::InputFloat2("Camera Rotation (y, z) axis (degree)", CameraRotation))
        {
            Camera.GetTransform().SetRotation(Camera.GetTransform().GetRotation().X, CameraRotation[0], CameraRotation[1]);
            
        }
        ImGui::DragFloat("Camera Speed", &Camera.CameraSpeed, 0.1f);

        FVector Forward = Camera.GetForward();
        FVector Up = Camera.GetUp();
        FVector Right = Camera.GetRight();
        
        ImGui::Text("Camera Forward: (%.2f %.2f %.2f)", Forward.X, Forward.Y, Forward.Z);
        ImGui::Text("Camera Up: (%.2f %.2f %.2f)", Up.X, Up.Y, Up.Z);
        ImGui::Text("Camera Right: (%.2f %.2f %.2f)", Right.X, Right.Y, Right.Z);
    
    }
    ImGui::End();

    AActor* selectedActor = nullptr;
    
    if (ImGui::Begin("Jungle Property Window"))
    {
        if (selectedActor != nullptr)
        {
            FTransform selectedTransform = selectedActor->GetActorTransform();
            float position[] = {selectedTransform.GetPosition().X, selectedTransform.GetPosition().Y, selectedTransform.GetPosition().Z};
            float rotation[] = {selectedTransform.GetRotation().X, selectedTransform.GetRotation().Y, selectedTransform.GetRotation().Z};
            float scale[] = {selectedTransform.GetScale().X, selectedTransform.GetScale().Y, selectedTransform.GetScale().Z};
            if (ImGui::DragFloat3("Translation", position, 0.1f))
            {
                selectedTransform.SetPosition(position[0], position[1], position[2]);
                selectedActor->SetTransform(selectedTransform);
            }
            if (ImGui::DragFloat3("Rotation", rotation, 0.1f))
            {
                selectedTransform.SetRotation(rotation[0], rotation[1], rotation[2]);
                selectedActor->SetTransform(selectedTransform);
            }
            if (ImGui::DragFloat3("Scale", scale, 0.1f))
            {
                selectedTransform.SetScale(scale[0], scale[1], scale[2]);
                selectedActor->SetTransform(selectedTransform);
            }
        }
    }
    ImGui::End();

    //if (ImGui::Begin("Console Window"))
    //{
    //    ImGui::Text("completion (TAB Key), history (Up/Down).");
    //    if (ImGui::Button("Add Debug Text"))
    //    {
    //    
    //    }
    //    ImGui::SameLine();
    //    if (ImGui::Button("Add Debug Error"))
    //    {
    //    
    //    }

    //    ImGui::SameLine();
    //    if (ImGui::Button("Clear"))
    //    {
    //    
    //    }
    //    ImGui::SameLine();
    //    if (ImGui::Button("Copy"))
    //    {
    //    
    //    }
    //}
    //    ImGui::End();
    Debug::ShowConsole(&bIsConsoleOpen);
    
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