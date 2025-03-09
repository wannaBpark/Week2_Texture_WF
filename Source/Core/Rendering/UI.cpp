#include "UI.h"

#include <algorithm>

#include "Camera.h"
#include "URenderer.h"
#include "Core/HAL/PlatformMemory.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Object/Actor/Actor.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"
#include "Object/ObjectFactory.h"
#include "Debug/DebugConsole.h"
#include <Object/Actor/Sphere.h>
#include <Object/Actor/Cube.h>

#include "Static/FEditorManager.h"


void UI::Initialize(HWND hWnd, const URenderer& Renderer, UINT ScreenWidth, UINT ScreenHeight)
{
    // ImGui 초기화
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // 기본 폰트 크기 설정
    io.FontGlobalScale = 1.0f;

    // ImGui Backend 초기화
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(Renderer.GetDevice(), Renderer.GetDeviceContext());

	ScreenSize = ImVec2(static_cast<float>(ScreenWidth), static_cast<float>(ScreenHeight));
    bIsInitialized = true;


    //ASphere* sphere = FObjectFactory::ConstructActor<ASphere>();
    //selectedActor = sphere;
}

void UI::Update()
{
    // ImGui Frame 생성
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    RenderControlPanel();
    RenderPropertyWindow();

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

void UI::OnUpdateWindowSize(UINT InScreenWidth, UINT InScreenHeight)
{
    // ImGUI 리소스 다시 생성
    ImGui_ImplDX11_InvalidateDeviceObjects();
    ImGui_ImplDX11_CreateDeviceObjects();
 //   // ImGui 창 크기 업데이트
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(static_cast<float>(InScreenWidth), static_cast<float>(InScreenHeight));
	ScreenSize = ImVec2(static_cast<float>(InScreenWidth), static_cast<float>(InScreenHeight));

 //   // 폰트 스케일 조정 (예: 창 높이에 비례하여 폰트 크기 조정)
 //   float scaleFactor = static_cast<float>(InScreenHeight) / 1080.0f; // 1080은 기준 해상도 높이
 //   io.FontGlobalScale = scaleFactor;
}

void UI::RenderControlPanel()
{
    // ImGui 창의 크기와 위치를 수동으로 조정
    ImGui::SetNextWindowSize(ImVec2(400, 600)); // 원하는 크기로 설정
    ImGui::SetNextWindowPos(ImVec2(50, 50));    // 원하는 위치로 설정
    if (ImGui::Begin("Jungle Control Panel"))
    {
        ImGui::Text("Hello, Jungle World!");
        ImGui::Text("FPS: %.3f (what is that ms)", ImGui::GetIO().Framerate);

        RenderMemoryUsage();
        RenderPrimitiveSelection();
        RenderCameraSettings();
    }
    ImGui::End();
}

void UI::RenderMemoryUsage()
{
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
}

void UI::RenderPrimitiveSelection()
{
    const char* items[] = { "Sphere", "Cube", "Triangle" };

    ImGui::Combo("Primitive", &currentItem, items, IM_ARRAYSIZE(items));

    if (ImGui::Button("Spawn"))
    {
        for (int i = 0; i < NumOfSpawn; i++)
        {
            if (strcmp(items[currentItem], "Sphere") == 0)
            {
                FObjectFactory::ConstructActor<ASphere>();
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
    if (ImGui::Button("Save Scene"))
    {
        // World.SaveWorld();   
    }
    if (ImGui::Button("Load Scene"))
    {
        // World.LoadWorld(SceneName);
    }
    ImGui::Separator();
}

void UI::RenderCameraSettings()
{
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

    float NearFar[2] = { Camera.GetNear(), Camera.GetFar() };
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

    float CameraLocation[] = { Camera.GetTransform().GetPosition().X, Camera.GetTransform().GetPosition().Y, Camera.GetTransform().GetPosition().Z };
    if (ImGui::DragFloat3("Camera Location", CameraLocation, 0.1f))
    {
        Camera.GetTransform().SetPosition(CameraLocation[0], CameraLocation[1], CameraLocation[2]);
    }

    float CameraRotation[] = { Camera.GetTransform().GetRotation().X, Camera.GetTransform().GetRotation().Y, Camera.GetTransform().GetRotation().Z };
    if (ImGui::DragFloat3("Camera Rotation", CameraRotation, 0.1f))
    {
        Camera.GetTransform().SetRotation(CameraRotation[0], CameraRotation[1], CameraRotation[2]);

    }
    ImGui::DragFloat("Camera Speed", &Camera.CameraSpeed, 0.1f);

    FVector Forward = Camera.GetForward();
    FVector Up = Camera.GetUp();
    FVector Right = Camera.GetRight();

    ImGui::Text("Camera Forward: (%.2f %.2f %.2f)", Forward.X, Forward.Y, Forward.Z);
    ImGui::Text("Camera Up: (%.2f %.2f %.2f)", Up.X, Up.Y, Up.Z);
    ImGui::Text("Camera Right: (%.2f %.2f %.2f)", Right.X, Right.Y, Right.Z);
}

void UI::RenderPropertyWindow()
{
    // bool bIsSelectedObjectExist = (UEngine::Get().World.GetSelected() != nullptr);
    bool bIsSelectedObjectExist = false;

    if (bIsSelectedObjectExist)
    {
        if (selectedActor != nullptr)
        {
            FTransform selectedTransform = selectedActor->GetActorTransform();
            //FTransform* selectedTransform = UEngine::Get().World.GetSelected().GetTransform();
            float position[] = { selectedTransform.GetPosition().X, selectedTransform.GetPosition().Y, selectedTransform.GetPosition().Z };
            float rotation[] = { selectedTransform.GetRotation().X, selectedTransform.GetRotation().Y, selectedTransform.GetRotation().Z };
            float scale[] = { selectedTransform.GetScale().X, selectedTransform.GetScale().Y, selectedTransform.GetScale().Z };
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
}
