#include "Camera.h"

Camera::Camera()
{
    Position = FVector();
    Rotation = FVector();
    Near = 1.f;
    Far = 1000.f;
    FieldOfView = 45.f;
		
    UpdateData();
}

void Camera::SetRotation(const float x, const float y, const float z)
{
    Rotation.X = x;
    Rotation.Y = y;
    Rotation.Z = z;

    UpdateData();
}

void Camera::UpdateData()
{
    float sinX = sin(Rotation.X * PI / 180.f);
    float cosX = cos(Rotation.X * PI / 180.f);
		
    float sinY = sin(Rotation.Y * PI / 180.f);
    float cosY = cos(Rotation.Y * PI / 180.f);
		
    float sinZ = sin(Rotation.Z * PI / 180.f);
    float cosZ = cos(Rotation.Z * PI / 180.f);


    Right = FVector(
        cosY * cosZ,                      // X
        sinX * sinY * cosZ + cosX * sinZ, // Y
        -cosX * sinY * cosZ + sinX * sinZ // Z
    );

    Up = FVector(
        cosY * -sinZ,                      // X
        sinX * sinY * -sinZ + cosX * cosZ, // Y
        -cosX * sinY * -sinZ + sinX * cosZ // Z
    );

    Forward = FVector(
        sinY,         // X
        -sinX * cosY, // Y
        cosX * cosY   // Z
    );
}

FMatrix Camera::GetViewMatrix() const
{
    return FMatrix::LookAtLH(Position, Position + Forward, Up);
}

FVector Camera::GetRotation() const
{
    return Rotation;
}