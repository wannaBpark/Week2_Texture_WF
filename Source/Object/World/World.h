#pragma once
#include <unordered_set>
#include "Object/UObject.h"
#include "Object/Actor/Actor.h"
#include "JsonSavehelper.h"

class UWorld :public UObject
{
public:
	void LoadWorld(const UWorldInfo& WorldInfo);
	void BeginPlay();
	void Tick(float DeltaTime);

protected:
	std::unordered_set<AActor*> Actors;
};

