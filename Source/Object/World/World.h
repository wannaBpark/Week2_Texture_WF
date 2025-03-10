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
	void BeginPlay();
	void Tick(float DeltaTime);
	void LateTick(float DeltaTime);
	
	void Render();
	void AddActor(class AActor* Actor) { Actors.Add(Actor); }

	void ClearWorld();
	void LoadWorld(const char* SceneName);
	void SaveWorld();
	
	// render
	void AddRenderComponent(class UPrimitiveComponent* Component) { RenderComponents.Add(Component); }
	void RemoveRenderComponent(class UPrimitiveComponent* Component) { RenderComponents.Remove(Component); }

private:
	UWorldInfo GetWorldInfo() const;

public:
	std::string SceneName = "";
	uint32 Version = 1;
	
protected:
	TSet<class AActor*> Actors;
	TSet<class UPrimitiveComponent*> RenderComponents;
};

