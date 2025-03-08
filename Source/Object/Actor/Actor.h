#pragma once
#include "Object/UObject.h"
#include "Object/USceneComponent.h"
#include "Core/Math/Transform.h"
#include "Core/Container/Set.h"
#include "Object/ObjectFactory.h"

class UWorld;

class AActor : public UObject
{
public:
	AActor() = default;
	virtual ~AActor() = default;

public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

	UWorld* GetWorld() const { return World; }
	void SetWorld(UWorld* InWorld) { World = InWorld; }

public:
	template<typename T>
		requires std::derived_from<T, USceneComponent>
	T* AddComponent()
	{
		T* ObjectInstance = FObjectFactory::ConstructObject<T>();
		Components.Add(ObjectInstance);

		return ObjectInstance;
	}

	// delete
	template<typename T>
		requires std::derived_from<T, USceneComponent>
	void RemoveComponent(T* Object)
	{
		Components.Remove(Object);
	}

	FTransform& GetTransform() { return Transform; }
	bool CanEverTick() const { return bCanEverTick; }

protected:
	bool bCanEverTick = true;
	TSet<USceneComponent*> Components;
	FTransform Transform;
	UWorld* World;
};

