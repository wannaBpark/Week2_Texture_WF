#include "Camera.h"

#include "Core/Rendering/URenderer.h"

FCamera::FCameraTransform::FCameraTransform() : Velocity{
    FVector(0, 0, 0)
}
{
    OnTranslate();
    OnRotate();
    UEngine::Get().GetRenderer()->UpdateViewMatrix(*this);
}

void FCamera::FCameraTransform::SetPosition(FVector InPosition)
{
    FTransform::SetPosition(InPosition);
    OnTranslate();
}

void FCamera::FCameraTransform::SetPosition(float x, float y, float z)
{
    FTransform::SetPosition(x, y, z);
    OnTranslate();
}

void FCamera::FCameraTransform::SetRotation(float x, float y, float z)
{
    FTransform::SetRotation(x, y, z);
    OnRotate();
}

void FCamera::FCameraTransform::SetRotation(FVector InRotation)
{
    FTransform::SetRotation(InRotation);
    OnRotate();
}

void FCamera::FCameraTransform::OnTranslate() const
{
    UEngine::Get().GetRenderer()->UpdateViewMatrix(*this);
}

void FCamera::FCameraTransform::OnRotate()
{
    float sinX = sin(Rotation.X * (PI / 180.f));
    float cosX = cos(Rotation.X * (PI / 180.f));
		
    float sinY = sin(Rotation.Y * (PI / 180.f));
    float cosY = cos(Rotation.Y * (PI / 180.f));
		
    float sinZ = sin(Rotation.Z * (PI / 180.f));
    float cosZ = cos(Rotation.Z * (PI / 180.f));


    Forward = FVector(
        cosY * cosZ,                      // X
        sinX * sinY * cosZ + cosX * sinZ, // Y
        -cosX * sinY * cosZ + sinX * sinZ // Z
    );

    Right = FVector::CrossProduct(Forward, FVector(0, 1, 0));

    Up = FVector::CrossProduct(Right, Forward);

    UEngine::Get().GetRenderer()->UpdateViewMatrix(*this);
}

FCamera::FCamera()
{
    Transform = FCamera::FCameraTransform();
    Near = 1.f;
    Far = 1000.f;
    FieldOfView = 45.f;
    ProjectionMode = ECameraProjectionMode::Perspective;
    
    OnUpdateProjectionChanges();
}

void FCamera::SetFieldOfVew(float Fov)
{
    FieldOfView = Fov;
    OnUpdateProjectionChanges();
}

void FCamera::SetFar(float Far)
{
    this->Far = Far;
    OnUpdateProjectionChanges();
}

void FCamera::SetNear(float Near)
{
    this->Near = Near;
    OnUpdateProjectionChanges();
}

float FCamera::GetFieldOfView() const
{
    return  FieldOfView;
}

float FCamera::GetNear() const
{
    return Near;
}

float FCamera::GetFar() const
{
    return Far;
}

FCamera::FCameraTransform& FCamera::GetTransform()
{
    return Transform;
}

void FCamera::OnUpdateProjectionChanges() const
{
    UEngine::Get().GetRenderer()->UpdateProjectionMatrix(*this);
}
