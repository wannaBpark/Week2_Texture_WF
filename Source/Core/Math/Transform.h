#pragma once
#include "Vector.h"
#include "Matrix.h"

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

};