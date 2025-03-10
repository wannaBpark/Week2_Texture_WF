#include "Camera.h"

#include "Core/Rendering/URenderer.h"



FCamera::FCamera()
{
    Transform = FCamera::FCameraTransform();
    Near = 1.f;
    Far = 1000.f;
    FieldOfView = 45.f;
    ProjectionMode = ECameraProjectionMode::Perspective;

    Transform.SetPosition(FVector(-5, 0, 0));
    
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
