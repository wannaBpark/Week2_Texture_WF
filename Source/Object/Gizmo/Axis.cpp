#include "Axis.h"

AAxis::AAxis()
{
	bIsGizmo = true;

	ULineComp* LineX = AddComponent<ULineComp>();
	FTransform XTransform;
	XTransform.SetScale(FVector(1000.0f, 1.0f, 1.0f));
	XTransform.SetRotation(FVector(0.0f, 0.0f, 0.0f));
	LineX->SetRelativeTransform(XTransform);
	LineX->SetCustomColor(FVector4(1.0f, 0.0f, 0.0f, 1.0f));

	ULineComp* LineY = AddComponent<ULineComp>();
	FTransform YTransform;
	YTransform.SetScale(FVector(1000.0f, 1.0f, 1.0f));
	YTransform.SetRotation(FVector(0.0f, 0.0f, 90.0f));
	LineY->SetRelativeTransform(YTransform);
	LineY->SetCustomColor(FVector4(0.0f, 1.0f, 0.0f, 1.0f));

	ULineComp* LineZ = AddComponent<ULineComp>();
	FTransform ZTransform;
	ZTransform.SetScale(FVector(1000.0f, 1.0f, 1.0f));
	ZTransform.SetRotation(FVector(0.0f, 90.0f, 0.0f));
	LineZ->SetRelativeTransform(ZTransform);
	LineZ->SetCustomColor(FVector4(0.0f, 0.0f, 1.0f, 1.0f));

	RootComponent = LineX;
	//LineY->SetupAttachment(LineX, true);
	//LineZ->SetupAttachment(LineX, true);
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
