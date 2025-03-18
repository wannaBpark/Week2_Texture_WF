#include "Object/Actor/WorldGrid.h"
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>

#include "Object/UClassManager.h"


AWorldGrid::AWorldGrid()
{
	EquipUClass(AWorldGrid, ClassType);

	bCanEverTick = true;

	UWorldGridComp* CubeComponent = AddComponent<UWorldGridComp>();
	RootComponent = CubeComponent;

	CubeComponent->SetRelativeTransform(FTransform());
}

void AWorldGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AWorldGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const char* AWorldGrid::GetTypeName()
{
	return "WorldGrid";
}

UClass* AWorldGrid::GetClass()
{
	return UClassManager::Get().GetClass<AWorldGrid>();
}
