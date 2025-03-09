#define _TCHAR_DEFINED

#include <unordered_map>

#include "Camera.h"
#include "PlayerInput.h"
#include "PlayerController.h"

APlayerController::APlayerController() {

}

void APlayerController::HandleCameraMovement(float DeltaTime) {

    FVector NewVelocity(0, 0, 0);

    if (APlayerInput::Get().IsPressedMouse(true) == false)
    {
        FCamera::Get().SetVelocity(NewVelocity);
        return;
    }
    //전프레임이랑 비교
    //x좌표 받아와서 x만큼 x축회전
    //y좌표 받아와서 y만큼 y축 회전
    FVector MousePrePos = APlayerInput::Get().GetMousePrePos();
    FVector MousePos = APlayerInput::Get().GetMousePos();
    FVector DeltaPos = MousePos - MousePrePos;
    FVector CameraRot = FCamera::Get().GetTransform().GetRotation();
    FCamera::Get().SetRotation(FVector(CameraRot.X, CameraRot.Y + DeltaPos.Y, CameraRot.Z + DeltaPos.X));

    float CamSpeed = FCamera::Get().CameraSpeed;

    if (APlayerInput::Get().IsPressedKey(EKeyCode::A)) {
        NewVelocity -= FCamera::Get().GetRight();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::D)) {
        NewVelocity += FCamera::Get().GetRight();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::W)) {
        NewVelocity += FCamera::Get().GetForward();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::S)) {
        NewVelocity -= FCamera::Get().GetForward();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::Q))
    {
        NewVelocity -= FCamera::Get().GetUp();
    }
    if (APlayerInput::Get().IsPressedKey(EKeyCode::E))
    {
        NewVelocity += FCamera::Get().GetUp();
    }
    if (NewVelocity.Length() > 0.001f)
    {
        NewVelocity = NewVelocity.GetSafeNormal();
    }

#pragma region TempMovement
    //회전이랑 마우스클릭 구현 카메라로 해야할듯?
    FVector NewPos = FCamera::Get().GetTransform().GetPosition() + (NewVelocity * DeltaTime * CamSpeed);
    FCamera::Get().GetTransform().SetPosition(NewPos); //임시용
#pragma endregion TempMovement
    // FCamera::Get().SetVelocity(NewVelocity);
}

void APlayerController::ProcessPlayerInput(float DeltaTime) {
    
    HandleCameraMovement(DeltaTime);
}
