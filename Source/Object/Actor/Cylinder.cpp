#include "Cylinder.h"

#include <Object/ActorComponent/Colliders/UBoxCollider.h>
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>
#include <Core/Engine.h>
#include <Object/World/World.h>

ACylinder::ACylinder()
{
    bCanEverTick = true;

    UCylinderComp* CylinderComponent = AddComponent<UCylinderComp>();
    RootComponent = CylinderComponent;

    hitCollider = AddComponent<UBoxCollider>();
    UEngine::Get().GetWorld()->AddColliderComponent(hitCollider);
    hitCollider->SetupAttachment(RootComponent);
    hitCollider->RelativeTransform.SetPosition(FVector(0, 0, 0.25));
    hitCollider->RelativeTransform.SetScale(FVector(0.03f, 0.03f, 0.2f));
	
    SetActorTransform(FTransform());
}

void ACylinder::BeginPlay()
{
    Super::BeginPlay();
}

void ACylinder::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

const char* ACylinder::GetTypeName()
{
    return "Cylinder";
}
