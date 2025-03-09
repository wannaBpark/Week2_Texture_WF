#include "Arrow.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"

AArrow::AArrow()
{
	UArrowComp* ArrowComp = AddComponent<UArrowComp>();
	RootComponent = ArrowComp;

}

void AArrow::BeginPlay()
{
	Super::BeginPlay();
}

void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
