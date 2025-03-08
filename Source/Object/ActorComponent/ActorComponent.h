#pragma once
#include "Object/UObject.h"
class UActorComponent : public UObject
{
public:
	UActorComponent() = default;
	virtual ~UActorComponent() = default;

	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
};

