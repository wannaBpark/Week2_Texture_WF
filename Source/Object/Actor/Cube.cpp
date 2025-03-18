#include "Cube.h"
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>
#include <Object/ActorComponent/Colliders/UBoxCollider.h>
#include <Core/Engine.h>
#include <Object/World/World.h>
#include "Object/UClassManager.h"

ACube::ACube()
{
	EquipUClass(ACube, ClassType);

	bCanEverTick = true;

	//UCubeComp* CubeComponent = AddComponent<UCubeComp>();
	ULightCubeComp* CubeComponent = AddComponent<ULightCubeComp>();
	RootComponent = CubeComponent;

	hitCollider = AddComponent<UBoxCollider>();
	UEngine::Get().GetWorld()->AddColliderComponent(hitCollider);
	hitCollider->SetupAttachment(RootComponent);

	CubeComponent->SetRelativeTransform(FTransform());
}

void ACube::BeginPlay()
{
	Super::BeginPlay();
}

void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const char* ACube::GetTypeName()
{
	return "Cube";
}

UClass* ACube::GetClass()
{
	return UClassManager::Get().GetClass<ACube>();
}
