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
    FVector Rotation;		// Read Only?
	
public:
    // Location - Vector3
    FVector Position;

    FVector Up;
    FVector Right;
    FVector Forward;
	
    // 투영 타입 - Perspective, Orthographic
    ECameraProjectionMode::Type ProjectionMode;
    // float AspectRatio;	// 카메라 비율 (이번 프로젝트에서는 사용 안할듯) 
	
    float Near;
    float Far;

    // 화면각
    float FieldOfView;


public:
    FCamera();
	
    void SetRotation(float x, float y, float z);

    void UpdateData();
	
	
    FMatrix GetViewMatrix() const;

    FVector GetRotation() const;

    void OnUpdateCamera();
};