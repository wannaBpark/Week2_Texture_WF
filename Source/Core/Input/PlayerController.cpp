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
    //FQuat CameraRot = FEditorManager::Get().GetCamera()->GetActorTransform().GetRotation();

    ACamera* Camera = FEditorManager::Get().GetCamera();
    FTransform camTransform = Camera->GetActorTransform();

    FVector TargetRotation = camTransform.GetRotation().GetEuler();
    TargetRotation.Y += Camera->CameraSpeed * DeltaPos.Y * DeltaTime;
    TargetRotation.Z += Camera->CameraSpeed * DeltaPos.X * DeltaTime;
    
    TargetRotation.Y = FMath::Clamp(TargetRotation.Y, -Camera->MaxYDegree, Camera->MaxYDegree);
    
    
    camTransform.SetRotation(TargetRotation);


    /*FQuat xDelta = FQuat(FVector(0, 0, 1), DeltaPos.X * DeltaTime);
	FQuat yDelta = FQuat(FVector(0, 1, 0), DeltaPos.Y * DeltaTime);
	FQuat newRot = FQuat::MultiplyQuaternions(CameraRot, xDelta);
	newRot = FQuat::MultiplyQuaternions(newRot, yDelta);*/


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

    //회전이랑 마우스클릭 구현 카메라로 해야할듯?
    camTransform.Translate(NewVelocity * DeltaTime * CamSpeed);
    Camera->SetActorTransform(camTransform); //임시용
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
