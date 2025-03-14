#include "Sphere.h"
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>
#include <Object/ActorComponent/Colliders/USphereCollider.h>
#include <Core/Engine.h>
#include <Object/World/World.h>

ASphere::ASphere()
{
	bCanEverTick = true;

	USphereComp* SphereComponent = AddComponent<USphereComp>();
	RootComponent = SphereComponent;
	USphereCollider* SphereCollider = AddComponent<USphereCollider>();
	SphereCollider->SetRadius(GetActorTransform().GetScale().X);
	UEngine::Get().GetWorld()->AddColliderComponent(SphereCollider);
	
	SetActorTransform(FTransform());
}

void ASphere::BeginPlay()
{
	Super::BeginPlay();
}

void ASphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const char* ASphere::GetTypeName()
{
	return "Sphere";
}
