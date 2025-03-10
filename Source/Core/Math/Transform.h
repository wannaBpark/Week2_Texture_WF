#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Core/Engine.h"

#define TORAD 0.0174532925199432957f

struct FTransform
{
protected:
	FVector Position;
	FQuat Rotation;
	FVector Scale;

public:
	FTransform()
		: Position(FVector(0, 0, 0))
		, Rotation(FQuat(0, 0, 0, 1))
		, Scale(FVector(1, 1, 1))
	{
	}

	FTransform(FVector InPosition, FVector InRotation, FVector InScale)
		: Position(InPosition)
		, Rotation(InRotation)
		, Scale(InScale)
	{
	}

	FTransform(FVector InPosition, FQuat InQuat, FVector InScale)
		: Position(InPosition)
		, Rotation(InQuat)
		, Scale(InScale)
	{
	}
	        
	inline FMatrix GetViewMatrix() const
	{
		return FMatrix::LookAtLH(Position, Position + GetForward(), GetUp());
	}
	
	inline virtual void SetPosition(const FVector& InPosition)
	{
		Position = InPosition;
	}
	inline virtual void SetPosition(float x, float y, float z)
	{
		Position = {x, y, z};
	}
	inline virtual void SetRotation(const FVector& InRotation)
	{
		Rotation = FQuat::EulerToQuaternion(InRotation);
	}
	inline virtual void SetRotation(float x, float y, float z)
	{
		SetRotation(FVector(x, y, z));
	}
	inline void SetScale(FVector InScale)
	{
		Scale = InScale;
	}

	inline virtual void SetRotation(const FQuat& InRotation)
	{
		Rotation = InRotation;
	}
	
	inline void SetScale(float x, float y, float z)
	{
		Scale = {x, y, z};
	}
	FVector GetPosition() const
	{
		return Position;
	}
	FQuat GetRotation() const 
	{
		return Rotation;
	}
	FVector GetEuler() const
	{
		return FQuat::QuaternionToEuler(Rotation);
	}

	FVector GetScale() const
	{
		return Scale;
	}

	FMatrix GetMatrix() const 
	{
		return FMatrix::Scale(Scale.X, Scale.Y, Scale.Z)
			* FMatrix::Rotate(Rotation)
			* FMatrix::Translate(Position.X, Position.Y, Position.Z);
	}

	FTransform ApplyParentTransform(const FTransform& ParentTransform) const
	{
		FMatrix ParentMatrix = ParentTransform.GetMatrix();
		FMatrix LocalMatrix = GetMatrix();

		FMatrix NewMatrix = ParentMatrix * LocalMatrix;

		FVector NewPosition = NewMatrix.GetTranslation();
		FVector NewRotation = NewMatrix.GetRotation();
		FVector NewScale = NewMatrix.GetScale();

		return FTransform(NewPosition, NewRotation, NewScale);
	}

	// void OnTranslate() const
	// {
	// 	UEngine::Get().GetRenderer()->UpdateViewMatrix(*this);
	// }

	FVector GetForward() const
	{
		float sinX = sin(Rotation.X * (PI / 180.f));
		float cosX = cos(Rotation.X * (PI / 180.f));
		
		float sinY = sin(Rotation.Y * (PI / 180.f));
		float cosY = cos(Rotation.Y * (PI / 180.f));
		
		float sinZ = sin(Rotation.Z * (PI / 180.f));
		float cosZ = cos(Rotation.Z * (PI / 180.f));
		
		return FVector(
			cosY * cosZ,                      // X
			sinX * sinY * cosZ + cosX * sinZ, // Y
			-cosX * sinY * cosZ + sinX * sinZ // Z
		).GetSafeNormal();
	}

	FVector GetRight() const
	{
		return FVector::CrossProduct(FVector(0, 0, 1), GetForward()).GetSafeNormal();
	}

	FVector GetUp() const{
		return FVector::CrossProduct(GetForward(), GetRight()).GetSafeNormal();

	}
};