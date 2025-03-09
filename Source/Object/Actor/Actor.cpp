#include "Actor.h"
#include "Object/USceneComponent.h"
#include <Debug/DebugConsole.h>

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

void AActor::Pick()
{
	if (RootComponent)
	{
		RootComponent->Pick(true);
	}
}

const FTransform& AActor::GetActorTransform()
{
	return RootComponent ? RootComponent->GetComponentTransform() : FTransform();
}

void AActor::SetTransform(const FTransform& InTransform)
{
	if (RootComponent)
	{
		RootComponent->SetTransform(InTransform);
	}
	else
	{
		UE_LOG("RootComponent is nullptr");
	}
}

USceneComponent* AActor::GetRootComponent()
{
	return RootComponent;
}
