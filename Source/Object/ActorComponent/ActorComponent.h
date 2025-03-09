#pragma once
#include "Core/EngineTypes.h"
#include "Object/UObject.h"

class UActorComponent : public UObject
{
public:
	UActorComponent() = default;

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
	virtual void EndPlay(const EEndPlayReason::Type Reason);

	bool CanEverTick() const { return bCanEverTick; }

protected:
	bool bCanEverTick = true;
};

