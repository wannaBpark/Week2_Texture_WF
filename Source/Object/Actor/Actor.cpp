#include "Actor.h"
#include "Object/USceneComponent.h"

void AActor::BeginPlay()
{
	for (auto& Component : Components)
	{
		Component->BeginPlay();
	}
}

void AActor::Tick(float DeltaTime)
{
	for (auto& Component : Components)
	{
		if (Component->CanEverTick())
		{
			Component->Tick(DeltaTime);
		}
	}
}

FTransform AActor::GetActorTransform()
{
	// TODO: 여기에 return 문을 삽입합니다.
	return RootComponent ? RootComponent->GetTransform() : FTransform();
}

USceneComponent* AActor::GetRootComponent()
{
	return RootComponent;
}
