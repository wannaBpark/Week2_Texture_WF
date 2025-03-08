#pragma once
#include "Vector.h"
#include "Matrix.h"

#define TORAD 0.0174532925199432957f

struct FTransform
{
private:
	FVector Position;
	FVector Rotation;
	FVector Scale;

public:
	FTransform()
		: Position(FVector(0, 0, 0))
		, Rotation(FVector(0, 0, 0))
		, Scale(FVector(1, 1, 1))
	{

	}
	inline void SetPosition(FVector InPosition)
	{
		Position = InPosition;
	}
	inline void SetRotation(FVector InRotation)
	{
		Rotation = InRotation;
	}
	inline void SetScale(FVector InScale)
	{
		Scale = InScale;
	}
	FVector GetPosition() const
	{
		return Position;
	}
	FVector GetRotation() const 
	{
		return Rotation;
	}
	FVector GetScale() const
	{
		return Scale;
	}

	FMatrix GetWorldMatrix() const 
	{
		return FMatrix::Translate(Position.X, Position.Y, Position.Z) 
			* FMatrix::Rotate(Rotation.X, Rotation.Y, Rotation.Z) 
			* FMatrix::Scale(Scale.X, Scale.Y, Scale.Z);
	}

	FVector GetForward() const
	{
		return FVector(
			std::cos(Rotation.Z * TORAD) * std::cos(Rotation.Y * TORAD),
			std::sin(Rotation.Y * TORAD),
			std::sin(Rotation.Z * TORAD) * std::cos(Rotation.Y * TORAD)
		).GetSafeNormal();
	}

	FVector GetRight() const
	{
		return FVector::CrossProduct(GetForward(), FVector(0, 1, 0));
	}

	FVector GetUp() const
	{
		return FVector::CrossProduct(GetRight(), GetForward());
	}
};