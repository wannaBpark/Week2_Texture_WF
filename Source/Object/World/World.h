#pragma once
#include "JsonSavehelper.h"
#include "Core/Engine.h"
#include "Core/Container/Array.h"
#include "Core/Container/Set.h"
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
	void BeginPlay();
	void Tick(float DeltaTime);
	void LateTick(float DeltaTime);

	template <typename T>
		requires std::derived_from<T, AActor>
	T* SpawnActor();
  
	bool DestroyActor(AActor* InActor);
	
	void Render();

	void ClearWorld();
	void LoadWorld(const char* SceneName);
	void SaveWorld();
	
	// render
	void AddRenderComponent(class UPrimitiveComponent* Component) { RenderComponents.Add(Component); }
	void RemoveRenderComponent(class UPrimitiveComponent* Component) { RenderComponents.Remove(Component); }

private:
	UWorldInfo GetWorldInfo() const;

public:
	std::string SceneName;
	uint32 Version = 1;
	
protected:
	TArray<AActor*> Actors;
	TArray<AActor*> ActorsToSpawn;
	TArray<AActor*> PendingDestroyActors; // TODO: 추후에 TQueue로 변경
	TSet<UPrimitiveComponent*> RenderComponents;
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
		ActorsToSpawn.Add(Actor);
		return Actor;
	}

	UE_LOG("Actor Construction Failed. World is nullptr");
	return nullptr;
}

