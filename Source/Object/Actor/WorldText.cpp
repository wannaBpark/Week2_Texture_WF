#include "Object/Actor/WorldText.h"
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>

AWorldText::AWorldText()
{
	bCanEverTick = true;

	UWorldTextComp* CubeComponent = AddComponent<UWorldTextComp>();
	RootComponent = CubeComponent;

	CubeComponent->SetRelativeTransform(FTransform());
}

void AWorldText::BeginPlay()
{
	Super::BeginPlay();
}

void AWorldText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const char* AWorldText::GetTypeName()
{
	return "WorldText";
}