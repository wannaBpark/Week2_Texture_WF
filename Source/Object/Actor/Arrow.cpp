#include "Arrow.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"

AArrow::AArrow()
{
	UArrowComp* ArrowComp = AddComponent<UArrowComp>();
	RootComponent = ArrowComp;

	ArrowComp->SetTransform(FTransform());
}

void AArrow::BeginPlay()
{
	Super::BeginPlay();
}

void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
