#pragma once
#include "Object/UObject.h"
#include "Core/Container/Set.h"

class UWorld :public UObject
{
public:
	UWorld() = default;
	virtual ~UWorld() = default;

public:
	void LoadWorld(const struct UWorldInfo& WorldInfo);
	void BeginPlay();
	void Tick(float DeltaTime);

protected:
	TSet<class AActor*> Actors;
};

