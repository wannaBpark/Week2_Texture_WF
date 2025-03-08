#include "Axis.h"

AAxis::AAxis()
{
} 

void AAxis::BeginPlay()
{
	Super::BeginPlay();
	ULineComp* LineX = AddComponent<ULineComp>();
	LineX->GetTransform().SetScale(FVector(1000.0f, 1.0f, 1.0f));
	LineX->GetTransform().SetRotation(FVector(0.0f, 0.0f, 0.0f));
	LineX->SetCustomColor(FVector4(1.0f, 0.0f, 0.0f, 1.0f));

	ULineComp* LineY = AddComponent<ULineComp>();
	LineY->GetTransform().SetScale(FVector(1000.0f, 1.0f, 1.0f));
	LineY->GetTransform().SetRotation(FVector(0.0f, 0.0f, 90.0f));
	LineY->SetCustomColor(FVector4(0.0f, 1.0f, 0.0f, 1.0f));

	ULineComp* LineZ = AddComponent<ULineComp>();
	LineZ->GetTransform().SetScale(FVector(1000.0f, 1.0f, 1.0f));
	LineZ->GetTransform().SetRotation(FVector(0.0f, 90.0f, 0.0f));
	LineZ->SetCustomColor(FVector4(0.0f, 0.0f, 1.0f, 1.0f));
}

void AAxis::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
