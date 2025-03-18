#include "Object/Actor/Circle.h"

#include <Object/PrimitiveComponent/UPrimitiveComponent.h>

#include "Object/UClassManager.h"

ACircle::ACircle()
{
    EquipUClass(ACircle, ClassType);

    bCanEverTick = true;

    UCircleComp* CircleComponent = AddComponent<UCircleComp>();
    RootComponent = CircleComponent;

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

UClass* ACircle::GetClass()
{
    return UClassManager::Get().GetClass<ACircle>();
}
