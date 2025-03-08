#include "AActor.h"

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
		Component->Tick(DeltaTime);
	}
}
