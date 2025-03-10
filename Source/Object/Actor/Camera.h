#pragma once

#include "Core/AbstractClass/Singleton.h"
#include "Core/HAL/PlatformType.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Transform.h"
#include "Core/Math/Vector.h"
#include "Object/Actor/Actor.h"

namespace ECameraProjectionMode
{
    enum Type : uint8
    {
        Perspective,
        Orthographic
    };
}

class FCamera : public AActor
{

    using Super = AActor;
    
public:
    FCamera() = default;
    ~FCamera() = default;
    
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual const char* GetTypeName() override;
private:    
    float Near;
    float Far;
    // 화면각
    float FieldOfView;

public:
    //카메라 스피드 IMGui용 나중에 Velocity로 관리하면 없어질애라 편하게 public에서 관리
    float CameraSpeed = 1.0f;
    
    // 투영 타입 - Perspective, Orthographic
    ECameraProjectionMode::Type ProjectionMode;
    // float AspectRatio;	// 카메라 비율 (이번 프로젝트에서는 사용 안할듯) 

    void SetFieldOfVew(float Fov);
    void SetFar(float Far);
    void SetNear(float Near);
    
    float GetFieldOfView() const;
    float GetNear() const;
    float GetFar() const;

    // void SetVelocity(FVector InVelocity){ GetActorTransform().SetVelocity() }
        
    FVector GetForward() const
    {
        return GetActorTransform().Forward;
    }
    
    FVector GetRight() const
    {
        return GetActorTransform().Right;
    }
    
    FVector GetUp() const
    {
        return GetActorTransform().Up;
    }

    FMatrix GetViewMatrix() const
    {
        return GetActorTransform().GetViewMatrix();
    }

    FVector GetVelocity() const { return GetActorTransform().Velocity; }
    
private:
    void OnUpdateProjectionChanges() const;
};