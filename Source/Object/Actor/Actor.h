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
	virtual ~AActor() = default;

public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

	UWorld* GetWorld() const { return World; }
	void SetWorld(UWorld* InWorld) { World = InWorld; }

public:
	virtual void Pick();

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

public:
	class USceneComponent* GetRootComponent();

protected:
	bool bCanEverTick = true;
	TSet<UActorComponent*> Components;
	USceneComponent* RootComponent = nullptr;
	//FTransform Transform;
	UWorld* World = nullptr;
};

