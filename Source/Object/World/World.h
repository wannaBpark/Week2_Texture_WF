#pragma once
#include "JsonSavehelper.h"
#include "Object/UObject.h"
#include "Core/Container/Set.h"

class UWorld :public UObject
{
public:
	UWorld() = default;
	virtual ~UWorld() = default;

public:
	void LoadWorld(const char* Name);
	void ClearWorld();
	UWorldInfo GetWorldInfo();
	void SaveWorld();
	void BeginPlay();
	void Tick(float DeltaTime);
	void AddActor(class AActor* Actor) { Actors.Add(Actor); }

public:
	std::string SceneName = "";
	
protected:
	TSet<class AActor*> Actors;
};

