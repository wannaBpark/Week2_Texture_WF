#pragma once

#include "Core/AbstractClass/Singleton.h"
#include "Core/HAL/PlatformType.h"
#include "Core/Math/Matrix.h"
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
private:
    // Rotation - Quaternion vs Vector3
    FVector Rotation;

    // Location - Vector3
    FVector Position;

    FVector Up;
    FVector Right;
    FVector Forward;

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

    void SetRotation(const float x, const float y, const float z);
    void SetRotation(const FVector& Rot);
    void SetPosition(const float x, const float y, const float z);
    void SetPosition(const FVector& Pos);

    void SetFieldOfVew(float Fov);
    void SetFar(float Far);
    void SetNear(float Near);
    
    
    FMatrix GetViewMatrix() const;
    FVector GetPosition() const;
    FVector GetRotation() const;

    FVector GetForward() const;
    FVector GetRight() const;
    FVector GetUp() const;

    float GetFieldOfView() const;
    float GetNear() const;
    float GetFar() const;


private:
    void OnUpdateTransform();
    void OnUpdateProjectionChanges() const;
};