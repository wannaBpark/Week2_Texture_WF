#include "Cube.h"
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>

ACube::ACube()
{
	bCanEverTick = true;

	UCubeComp* CubeComponent = AddComponent<UCubeComp>();
	FTransform CubeTransform;
	CubeTransform.SetScale(FVector(1.0f, 1.0f, 1.0f));
	CubeTransform.SetRotation(FVector(0.0f, 0.0f, 0.0f));
	CubeComponent->SetTransform(CubeTransform);

	RootComponent = CubeComponent;
}

void ACube::BeginPlay()
{
	Super::BeginPlay();
}

void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
