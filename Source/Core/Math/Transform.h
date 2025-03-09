#pragma once
#include "Vector.h"
#include "Matrix.h"

#define TORAD 0.0174532925199432957f

struct FTransform
{
protected:
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

	FTransform(FVector InPosition, FVector InRotation, FVector InScale)
		: Position(InPosition)
		, Rotation(InRotation)
		, Scale(InScale)
	{
	}

	virtual ~FTransform() = default;
	
	inline virtual void SetPosition(FVector InPosition)
	{
		Position = InPosition;
	}
	inline virtual void SetPosition(float x, float y, float z)
	{
		Position = {x, y, z};
	}
	inline virtual void SetRotation(FVector InRotation)
	{
		Rotation = InRotation;
	}
	inline virtual void SetRotation(float x, float y, float z)
	{
		Rotation = {x, y, z};
	}
	inline void SetScale(FVector InScale)
	{
		Scale = InScale;
	}
	inline void SetScale(float x, float y, float z)
	{
		Scale = {x, y, z};
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

	FTransform operator*(const FTransform& Other) const
	{
		FMatrix ParentMatrix = GetWorldMatrix();
		FMatrix ChildMatrix = Other.GetWorldMatrix();

		FMatrix Result = ParentMatrix * ChildMatrix;

		FVector ResultPosition = Result.GetTranslation();
		FVector ResultRotation = Result.GetRotation();
		FVector ResultScale = Result.GetScale();

		return FTransform(ResultPosition, ResultRotation, ResultScale);
	}

	// FVector GetForward() const
	// {
	// 	return FVector(
	// 		std::cos(Rotation.Z * TORAD) * std::cos(Rotation.Y * TORAD),
	// 		std::sin(Rotation.Y * TORAD),
	// 		std::sin(Rotation.Z * TORAD) * std::cos(Rotation.Y * TORAD)
	// 	).GetSafeNormal();
	// }
};