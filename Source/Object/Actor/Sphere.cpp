#include "Sphere.h"
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>

ASphere::ASphere()
{
	bCanEverTick = true;

	USphereComp* SphereComponent = AddComponent<USphereComp>();
	FTransform SphereTransform;
	SphereTransform.SetScale(FVector(1.0f, 1.0f, 1.0f));
	SphereTransform.SetRotation(FVector(0.0f, 0.0f, 0.0f));
	SphereComponent->SetTransform(SphereTransform);

	RootComponent = SphereComponent;
}

void ASphere::BeginPlay()
{
	Super::BeginPlay();
}

void ASphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
