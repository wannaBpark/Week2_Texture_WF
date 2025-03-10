#include "PlayerController.h"

#include <unordered_map>
#include "Object//Actor/Camera.h"
#include "PlayerInput.h"
#include "Static/FEditorManager.h"
#include "Core/Math/Plane.h"

APlayerController::APlayerController() {

}

void APlayerController::HandleCameraMovement(float DeltaTime) {

    FVector NewVelocity(0, 0, 0);

    if (APlayerInput::Get().IsPressedMouse(true) == false)
    {
        // Camera->SetVelocity(NewVelocity);
        return;
    }

    ACamera* Camera = FEditorManager::Get().GetCamera();
    
    //전프레임이랑 비교
    //x좌표 받아와서 x만큼 x축회전
    //y좌표 받아와서 y만큼 y축 회전
    FVector MousePrePos = APlayerInput::Get().GetMousePrePos();
    FVector MousePos = APlayerInput::Get().GetMousePos();
    FVector DeltaPos = MousePos - MousePrePos;

    FQuat CameraRot = Camera->GetActorTransform().GetRotation();
    FQuat DeltaQuaternion = FQuat::EulerToQuaternion(FVector(0.0f, DeltaPos.Y, DeltaPos.X));
    FQuat NewQuat = FQuat::MultiplyQuaternions(CameraRot, FQuat::AddQuaternions(CameraRot, DeltaQuaternion));

    FTransform NewTransf = Camera->GetActorTransform();
    NewTransf.SetRotation(FQuat::AddQuaternions(CameraRot, DeltaQuaternion));
    Camera->SetActorTransform(NewTransf);
    
    float CamSpeed = Camera->CameraSpeed;

    if (APlayerInput::Get().IsPressedKey(EKeyCode::A)) {
        NewVelocity -= Camera->GetRight();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::D)) {
        NewVelocity += Camera->GetRight();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::W)) {
        NewVelocity += Camera->GetForward();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::S)) {
        NewVelocity -= Camera->GetForward();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::Q))
    {
        NewVelocity -= Camera->GetUp();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::E))
    {
        NewVelocity += Camera->GetUp();
    }
    if (NewVelocity.Length() > 0.001f)
    {
        NewVelocity = NewVelocity.GetSafeNormal();
    }

#pragma region TempMovement
    //회전이랑 마우스클릭 구현 카메라로 해야할듯?
    FVector NewPos = Camera->GetActorTransform().GetPosition() + (NewVelocity * DeltaTime * CamSpeed);
    Camera->GetActorTransform().SetPosition(NewPos); //임시용

    FTransform Transform = Camera->GetActorTransform();
    Transform.SetPosition(NewPos);
    Camera->SetActorTransform(Transform);
    
#pragma endregion TempMovement
    // FCamera::Get().SetVelocity(NewVelocity);
}

void APlayerController::HandleGizmoMovement(float DeltaTime)
{
    if (APlayerInput::Get().IsPressedMouse(false) == false)
    {
        return;
    }

    AActor* SelectedActor = FEditorManager::Get().GetSelectedActor();
    
    if (SelectedActor == nullptr) //이거를 나중엔 기즈모로 체크
    {
        return;
    }

    
}

void APlayerController::ProcessPlayerInput(float DeltaTime) {

    HandleGizmoMovement(DeltaTime);
    HandleCameraMovement(DeltaTime);
}
