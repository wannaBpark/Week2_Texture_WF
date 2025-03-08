#include "World.h"

void UWorld::LoadWorld(const UWorldInfo& WorldInfo)
{
	// !TODO : WorldInfo에 맞게 오브젝트들 Instantiate
}

void UWorld::BeginPlay()
{
	for (auto& Actor : Actors)
	{
		Actor->BeginPlay();
	}
}

void UWorld::Tick(float DeltaTime)
{
	for (auto& Actor : Actors)
	{
		if (Actor->CanEverTick())
		{
			Actor->Tick(DeltaTime);
		}
	}
}
