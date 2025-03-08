#pragma once
#include "Object/UObject.h"
#include "Object/USceneComponent.h"
#include "Object/FObjectFactory.h"
#include "Core/Math/Transform.h"
#include "Core/Container/Set.h"
#include <memory>
#include <unordered_set>

class AActor : public UObject
{
public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

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
	bool bCanEverTick = false;
	TSet<USceneComponent*> Components;
	FTransform Transform;
};

