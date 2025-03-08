#include "USceneComponent.h"

void USceneComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USceneComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FTransform& USceneComponent::GetTransform()
{
	FTransform transform;


	// I don't understand well
	
	transform.SetPosition(Transform.GetPosition());	// Temp
	transform.SetRotation(transform.GetRotation());	// Temp
	transform.SetScale(Transform.GetScale() * Parent->GetScale());
	return Transform;



	// GetWorldMatrix -> scale * rotation * transform 
	// rotation
	// FMatrix matrix = Parent->GetWorldMatrix() * Transform.GetWorldMatrix();
	// FTransform Result;
	// Result.SetPosition(matrix.M[0][3], matrix.M[1][3], matrix.M[2][3]);
	//
	// float sx = FVector(matrix.M[0][0], matrix.M[1][0], matrix.M[2][0]).Length();
	// float sy = FVector(matrix.M[0][1], matrix.M[1][1], matrix.M[2][1]).Length();
	// float sz = FVector(matrix.M[0][2], matrix.M[1][2], matrix.M[2][2]).Length();
	//
	// // y, z, x
	// Result.SetScale(sx, sy, sz);
	//
	// FMatrix RotMatrix = {{matrix.M[0][0] / sx, matrix.M[1][0] / sx, matrix.M[2][0] / sx, 0},
	// 	{matrix.M[0][1] / sy, matrix.M[1][1] / sy, matrix.M[2][1] / sy, 0},
	// 	{matrix.M[0][2] / sz, matrix.M[1][2] / sz, matrix.M[2][2] / sz, 0},
	// 	{0, 0, 0, 1}};
	//
	// float thetaZ = atan2(matrix.M[1][0], matrix.M[0][0]);
	// float thetaY = -atan2(matrix.M[2][0], sqrt(matrix.M[2][1] * matrix.M[2][1] + matrix.M[2][2] * matrix.M[2][2]));
	// float thetaX = atan2(matrix.M[2][1], matrix.M[2][2]);
	//
	// Result.SetRotation(thetaX, thetaY, thetaZ);
	// 	
	// return Result;
}
