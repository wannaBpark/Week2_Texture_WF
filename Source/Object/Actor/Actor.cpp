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

void AActor::Pick()
{
	if (RootComponent)
	{
		RootComponent->Pick(true);
	}
}

void AActor::UnPick()
{
	if (RootComponent)
	{
		RootComponent->Pick(false);
	}	
}

const FTransform& AActor::GetActorTransform()
{
	return RootComponent ? RootComponent->GetComponentTransform() : FTransform();
}

void AActor::SetActorTransform(const FTransform& InTransform)
{
	// InTransform은 월드 기준임
	if (RootComponent)
	{
		RootComponent->SetRelativeTransform(InTransform);
	}
	else
	{
		UE_LOG("RootComponent is nullptr");
	}
}

const char* AActor::GetTypeName()
{
	return "Actor";
}

USceneComponent* AActor::GetRootComponent()
{
	return RootComponent;
}

bool AActor::Destroy()
{
	return GetWorld()->DestroyActor(this);
}
