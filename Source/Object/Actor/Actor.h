#pragma once
#include "Object/UObject.h"
#include "Object/ActorComponent/ActorComponent.h"
#include "Core/Math/Transform.h"
#include "Core/Container/Set.h"
#include "Object/ObjectFactory.h"

class UWorld;

class AActor : public UObject
{
public:
	AActor() = default;
	virtual ~AActor();

public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

	UWorld* GetWorld() const { return World; }
	void SetWorld(UWorld* InWorld) { World = InWorld; }

public:
	template<typename T>
		requires std::derived_from<T, UActorComponent>
	T* AddComponent()
	{
		T* ObjectInstance = FObjectFactory::ConstructObject<T>();
		ObjectInstance->Initialize(&Transform);
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

	FTransform& GetTransform() { return Transform; }
	bool CanEverTick() const { return bCanEverTick; }

protected:
	bool bCanEverTick = true;
	TSet<UActorComponent*> Components;
	FTransform Transform;
	UWorld* World = nullptr;
};

