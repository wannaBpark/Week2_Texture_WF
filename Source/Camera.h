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
    private:
        FVector Up;
        FVector Right;
        FVector Forward;

    public:
        FCameraTransform();
    
        inline void SetPosition(FVector InPosition) override;
        inline void SetPosition(float x, float y, float z) override;
        inline void SetRotation(float x, float y, float z) override;
        inline void SetRotation(FVector InRotation) override;
        void OnTranslate() const;
        void OnRotate();

        inline FVector GetForward() const
        {
            return Forward;
        }
    
        inline FVector GetRight() const
        {
            return Right;
        }
    
        inline FVector GetUp() const
        {
            return Up;
        }

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
    // 투영 타입 - Perspective, Orthographic
    ECameraProjectionMode::Type ProjectionMode;
    // float AspectRatio;	// 카메라 비율 (이번 프로젝트에서는 사용 안할듯) 

public:
    FCamera();

    FCameraTransform& GetTransform();

    void SetFieldOfVew(float Fov);
    void SetFar(float Far);
    void SetNear(float Near);
    
    float GetFieldOfView() const;
    float GetNear() const;
    float GetFar() const;

private:
    void OnUpdateProjectionChanges() const;
};