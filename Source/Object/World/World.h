#pragma once
#include "JsonSavehelper.h"
#include "Core/Engine.h"
#include "Core/Container/Array.h"
#include "Object/UObject.h"
#include "Debug/DebugConsole.h"
#include "Object/ObjectFactory.h"

class AActor;


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

	template <typename T>
		requires std::derived_from<T, AActor>
	T* SpawnActor();

public:
	std::string SceneName;
	
protected:
	TArray<AActor*> Actors;
};

template <typename T>
	requires std::derived_from<T, AActor>
T* UWorld::SpawnActor()
{
	T* Actor = FObjectFactory::ConstructObject<T>();
	
	if (UWorld* World = UEngine::Get().GetWorld())
	{
		Actor->SetWorld(World);
		Actors.Add(Actor);
		return Actor;
	}

	UE_LOG("Actor Construction Failed. World is nullptr");
	return nullptr;
}

