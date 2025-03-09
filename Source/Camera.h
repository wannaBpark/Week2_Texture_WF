#pragma once

#include "Core/AbstractClass/Singleton.h"
#include "Core/HAL/PlatformType.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Transform.h"
#include "Core/Math/Vector.h"

namespace ECameraProjectionMode
{
    enum Type : uint8
    {
        Perspective,
        Orthographic
    };
}

class FCamera : public TSingleton<FCamera>
{
public:
    struct FCameraTransform : public FTransform
    {
    public:
        FVector Up;
        FVector Right;
        FVector Forward;
        FVector Velocity;

        FCameraTransform();
    
        void OnTranslate() const;
        void OnRotate();

        inline void SetPosition(FVector InPosition) override;
        inline void SetPosition(float x, float y, float z) override;
        inline void SetRotation(float x, float y, float z) override;
        inline void SetRotation(FVector InRotation) override;
        
        inline FMatrix GetViewMatrix() const
        {
            return FMatrix::LookAtLH(Position, Position + Forward, Up);
        }
    };
private:    
    FCameraTransform Transform;
    
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

    FCamera();

    FCameraTransform& GetTransform();

    void SetFieldOfVew(float Fov);
    void SetFar(float Far);
    void SetNear(float Near);
    
    float GetFieldOfView() const;
    float GetNear() const;
    float GetFar() const;

    void SetPosition(FVector InPosition);
    void SetPosition(float x, float y, float z);
    void SetRotation(float x, float y, float z);
    void SetRotation(FVector InRotation) {Transform.SetRotation(InRotation);};
    void SetVelocity(FVector InVelocity){ Transform.Velocity = InVelocity; }
        
    FVector GetForward() const
    {
        return Transform.Forward;
    }
    
    FVector GetRight() const
    {
        return Transform.Right;
    }
    
    FVector GetUp() const
    {
        return Transform.Up;
    }

    FMatrix GetViewMatrix() const
    {
        return Transform.GetViewMatrix();
    }

    FVector GetVelocity() const { return Transform.Velocity; }
    
private:
    void OnUpdateProjectionChanges() const;
};