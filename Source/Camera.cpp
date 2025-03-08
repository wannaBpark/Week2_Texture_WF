#include "Camera.h"

#include "Core/Rendering/URenderer.h"

FCamera::FCamera()
{
    Position = FVector();
    Rotation = FVector();
    Near = 1.f;
    Far = 1000.f;
    FieldOfView = 45.f;
		
    OnUpdateTransform();
    OnUpdateProjectionChanges();
}

void FCamera::SetRotation(const float x, const float y, const float z)
{
    SetRotation({x, y, z});
}

void FCamera::SetRotation(const FVector& Rot)
{
    Rotation = Rot;
    OnUpdateTransform();
}

void FCamera::SetPosition(const float x, const float y, const float z)
{
    SetPosition(FVector(x, y, z));
}

void FCamera::SetPosition(const FVector& Pos)
{
    Position = Pos;
    OnUpdateTransform();
}

void FCamera::SetFieldOfVew(float Fov)
{
    FieldOfView = Fov;
}

void FCamera::SetFar(float Far)
{
    this->Far = Far;
}

void FCamera::SetNear(float Near)
{
    this->Near = Near;
}

FVector FCamera::GetPosition() const
{
    return Position;
}

FVector FCamera::GetRotation() const
{
    return Rotation;
}

FVector FCamera::GetForward() const
{
    return Forward;
}

FVector FCamera::GetRight() const
{
    return Right;
}

FVector FCamera::GetUp() const
{
    return Up;
}

float FCamera::GetFieldOfView() const
{
    return FieldOfView;
}

FMatrix FCamera::GetViewMatrix() const
{
    return FMatrix::LookAtLH(Position, Position + Forward, Up);
}

float FCamera::GetNear() const
{
    return Near;
}

float FCamera::GetFar() const
{
    return Far;
}

void FCamera::OnUpdateTransform()
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

    UEngine::Get().GetRenderer()->UpdateViewMatrix(*this);
}

void FCamera::OnUpdateProjectionChanges() const
{
    UEngine::Get().GetRenderer()->UpdateProjectionMatrix(*this);
}
