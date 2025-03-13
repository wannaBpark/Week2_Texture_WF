#include "Circle.h"

#include <Object/PrimitiveComponent/UPrimitiveComponent.h>

ACircle::ACircle()
{
    bCanEverTick = true;

    UCylinderComp* CylinderComponent = AddComponent<UCylinderComp>();
    RootComponent = CylinderComponent;

    SetActorTransform(FTransform());
}

void ACircle::BeginPlay()
{
    Super::BeginPlay();
}

void ACircle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

const char* ACircle::GetTypeName()
{
    return "Circle";
}