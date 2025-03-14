#include "Cube.h"
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>
#include "Object/UClassManager.h"



UClass* ACube::GetClass()
{
	return UClassManager::Get().GetClass<ACube>();
}

ACube::ACube()
{
	EquipUClass(ACube, ClassType);

	bCanEverTick = true;

	UCubeComp* CubeComponent = AddComponent<UCubeComp>();
	RootComponent = CubeComponent;

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
