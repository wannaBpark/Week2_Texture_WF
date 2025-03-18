#include "Object/Actor/Triangle.h"
#include <Object/PrimitiveComponent/UPrimitiveComponent.h>

#include "Object/UClassManager.h"

ATriangle::ATriangle()
{
	EquipUClass(ATriangle, ClassType);

	bCanEverTick = true;

	UTriangleComp* CubeComponent = AddComponent<UTriangleComp>();
	RootComponent = CubeComponent;

	CubeComponent->SetRelativeTransform(FTransform());
}

void ATriangle::BeginPlay()
{
	Super::BeginPlay();
}

void ATriangle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const char* ATriangle::GetTypeName()
{
	return "Triangle";
}

UClass* ATriangle::GetClass()
{
	return UClassManager::Get().GetClass<ATriangle>();
}
