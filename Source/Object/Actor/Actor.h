#pragma once
#include "Object/UObject.h"
#include "Object/ActorComponent/ActorComponent.h"
#include "Core/Math/Transform.h"
#include "Core/Container/Set.h"
#include "Object/ObjectFactory.h"
#include "Object/USceneComponent.h"

class UWorld;

class AActor : public UObject
{
public:
	AActor() = default;
	virtual ~AActor() override = default;

public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);
	virtual void Destroyed();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UWorld* GetWorld() const { return World; }
	void SetWorld(UWorld* InWorld) { World = InWorld; }

public:
	template<typename T>
		requires std::derived_from<T, UActorComponent>
	T* AddComponent()
	{
		T* ObjectInstance = FObjectFactory::ConstructObject<T>();
		Components.Add(ObjectInstance);

		return ObjectInstance;
	}

	// delete
	template<typename T>
		requires std::derived_from<T, UActorComponent>
	void RemoveComponent(T* Object)
	{
		Components.Remove(Object);
	}

	const FTransform& GetActorTransform();
	void SetTransform(const FTransform& InTransform);
	bool CanEverTick() const { return bCanEverTick; }

	bool Destroy();

public:
	USceneComponent* GetRootComponent() const { return RootComponent; }
	void SetRootComponent(USceneComponent* InRootComponent) { RootComponent = InRootComponent; }

protected:
	bool bCanEverTick = true;
	USceneComponent* RootComponent = nullptr;

private:
	UWorld* World = nullptr;
	TSet<UActorComponent*> Components;
};

