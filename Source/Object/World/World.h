#pragma once
#include "Object/UObject.h"
#include "Object/Actor/Actor.h"
#include "Core/Container/Set.h"
#include "JsonSavehelper.h"

class UWorld :public UObject
{
public:
	void LoadWorld(const UWorldInfo& WorldInfo);
	void BeginPlay();
	void Tick(float DeltaTime);

protected:
	TSet<AActor*> Actors;
};

