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
        // FEditorManager::Get().GetCamera()->SetVelocity(NewVelocity);
        return;
    }
    //전프레임이랑 비교
    //x좌표 받아와서 x만큼 x축회전
    //y좌표 받아와서 y만큼 y축 회전
    FVector MousePrePos = APlayerInput::Get().GetMousePrePos();
    FVector MousePos = APlayerInput::Get().GetMousePos();
    FVector DeltaPos = MousePos - MousePrePos;

    FQuaternion CameraRot = FEditorManager::Get().GetCamera()->GetActorTransform().GetRotation();
    FQuaternion DeltaQuaternion = FQuaternion::EulerToQuaternion(FVector(0.0f, DeltaPos.Y, DeltaPos.X));
    FEditorManager::Get().GetCamera()->GetActorTransform().SetRotation(FQuaternion::AddQuaternions(CameraRot, DeltaQuaternion));


    float CamSpeed = FEditorManager::Get().GetCamera()->CameraSpeed;

    if (APlayerInput::Get().IsPressedKey(EKeyCode::A)) {
        NewVelocity -= FEditorManager::Get().GetCamera()->GetRight();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::D)) {
        NewVelocity += FEditorManager::Get().GetCamera()->GetRight();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::W)) {
        NewVelocity += FEditorManager::Get().GetCamera()->GetForward();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::S)) {
        NewVelocity -= FEditorManager::Get().GetCamera()->GetForward();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::Q))
    {
        NewVelocity -= FEditorManager::Get().GetCamera()->GetUp();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::E))
    {
        NewVelocity += FEditorManager::Get().GetCamera()->GetUp();
    }
    if (NewVelocity.Length() > 0.001f)
    {
        NewVelocity = NewVelocity.GetSafeNormal();
    }

#pragma region TempMovement
    //회전이랑 마우스클릭 구현 카메라로 해야할듯?
    FVector NewPos = FEditorManager::Get().GetCamera()->GetActorTransform().GetPosition() + (NewVelocity * DeltaTime * CamSpeed);
    FEditorManager::Get().GetCamera()->GetActorTransform().SetPosition(NewPos); //임시용

    FTransform Transform = FEditorManager::Get().GetCamera()->GetActorTransform();
    Transform.SetPosition(NewPos);
    FEditorManager::Get().GetCamera()->SetActorTransform(Transform);
    
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
