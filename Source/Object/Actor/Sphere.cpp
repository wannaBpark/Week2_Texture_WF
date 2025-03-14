#include "Sphere.h"
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>
#include "Object/UClassManager.h"

UClass* ASphere::GetClass()
{
	return UClassManager::Get().GetClass<ASphere>();
}

ASphere::ASphere()
{
	EquipUClass(ASphere, ClassType);

	bCanEverTick = true;

	USphereComp* SphereComponent = AddComponent<USphereComp>();
	RootComponent = SphereComponent;
	
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


