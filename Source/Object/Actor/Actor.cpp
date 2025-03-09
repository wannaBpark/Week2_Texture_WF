#include "Actor.h"
#include "Object/USceneComponent.h"
#include "Debug/DebugConsole.h"
#include "Object/World/World.h"

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

void AActor::Destroyed()
{
	EndPlay(EEndPlayReason::Destroyed);
}

void AActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (auto& Component : Components)
	{
		Component->EndPlay(EndPlayReason);
		UEngine::Get().GObjects.Remove(Component->shared_from_this());
	}
}

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

bool AActor::Destroy()
{
	return GetWorld()->DestroyActor(this);
}
