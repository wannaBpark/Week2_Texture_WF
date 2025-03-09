#include "Arrow.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"

AArrow::AArrow()
{
	bCanEverTick = true;

	UCylinderComp* CylinderComp = AddComponent<UCylinderComp>();
	RootComponent = CylinderComp;

	UConeComp* ConeComp = AddComponent<UConeComp>();
	ConeComp->SetTransform(FTransform(FVector(0.0f, 0.0f, 1.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.2f, 1.2f, 0.5f)));

	ConeComp->SetupAttachment(RootComponent);
}

void AArrow::BeginPlay()
{
	Super::BeginPlay();
}

void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
