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

void Camera::Rotate(const float x, const float y, const float z)
{
	Rotation.X = x;
	Rotation.Y = y;
	Rotation.Z = z;

	UpdateData();
}

void Camera::UpdateData()
{
	float sinX = sin(Rotation.X * 3.141592f / 180.f);
	float cosX = cos(Rotation.X * 3.141592f / 180.f);
		
	float sinY = sin(Rotation.Y * 3.141592f / 180.f);
	float cosY = cos(Rotation.Y * 3.141592f / 180.f);
		
	float sinZ = sin(Rotation.Z * 3.141592f / 180.f);
	float cosZ = cos(Rotation.Z * 3.141592f / 180.f);
		
	Right = FVector(
			cosY * cosZ,              // X
			sinX * sinY * cosZ + cosX * sinZ,  // Y
			-cosX * sinY * cosZ + sinX * sinZ // Z
		).Normalize();

	Up = FVector(
				cosY * -sinZ,            // X
				sinX * sinY * -sinZ + cosX * cosZ, // Y
				-cosX * sinY * -sinZ + sinX * cosZ // Z
			).Normalize();

	Forward = FVector(
				sinY, // X
				-sinX * cosY,  // Y
				cosX * cosY    // Z
			).Normalize();
}

DirectX::FXMMATRIX Camera::GetViewMatrix() const
{
	return DirectX::FXMMATRIX{
		 			{Right.X, Up.X, Forward.X, 0},
					{Right.Y, Up.Y, Forward.Y, 0},
					{Right.Z, Up.Z, Forward.Z, 0},
					{ -Position.Dot(Right), -Position.Dot(Up), -Position.Dot(Forward), 1 }
	};
}

FVector Camera::GetRotation() const
{
	return Rotation;
}