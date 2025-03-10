#include "Axis.h"

AAxis::AAxis()
{
	bIsGizmo = true;

	ULineComp* LineX = AddComponent<ULineComp>();
	FTransform XTransform = LineX->GetComponentTransform();
	XTransform.SetScale(FVector(1000.0f, 1.0f, 1.0f));
	XTransform.SetRotation(FVector(0.0f, 0.0f, 0.0f));
	LineX->SetRelativeTransform(XTransform);
	LineX->SetCustomColor(FVector4(1.0f, 0.0f, 0.0f, 1.0f));

	FVector Euler = LineX->GetComponentTransform().GetRotation().GetEuler();
	UE_LOG("LineX Rot: %f, %f, %f", 
		Euler.X,
		Euler.Y,
		Euler.Z
	);

	RootComponent = LineX;

	ULineComp* LineY = AddComponent<ULineComp>();
	FTransform YTransform = LineY->GetComponentTransform();
	YTransform.SetScale(FVector(1000.0f, 1.0f, 1.0f));
	YTransform.SetRotation(FVector(0.0f, 0.0f, 90.0f));
	LineY->SetRelativeTransform(YTransform);
	LineY->SetCustomColor(FVector4(0.0f, 1.0f, 0.0f, 1.0f));


	Euler = LineY->GetComponentTransform().GetRotation().GetEuler();
	UE_LOG("LineY Rot: %f, %f, %f",
		Euler.X,
		Euler.Y,
		Euler.Z
	);

	ULineComp* LineZ = AddComponent<ULineComp>();
	FTransform ZTransform;
	ZTransform.SetScale(FVector(1000.0f, 1.0f, 1.0f));
	ZTransform.SetRotation(FVector(0.0f, 90.0f, 0.0f));
	LineZ->SetRelativeTransform(ZTransform);
	LineZ->SetCustomColor(FVector4(0.0f, 0.0f, 1.0f, 1.0f));

	Euler = LineZ->GetComponentTransform().GetRotation().GetEuler();
	UE_LOG("LineZ Rot: %f, %f, %f",
		Euler.X,
		Euler.Y,
		Euler.Z
	);

} 

void AAxis::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAxis::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const char* AAxis::GetTypeName()
{
	return "Axis";
}
