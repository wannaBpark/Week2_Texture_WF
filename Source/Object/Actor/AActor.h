#pragma once
#include "Object/UObject.h"
#include "Object/USceneComponent.h"
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
		std::shared_ptr<T> = FObjectFactory::ConstructObject<T>();
		Components.insert(T);
	}

	// delete
	template<typename T>
		requires std::derived_from<T, USceneComponent>
	void RemoveComponent()
	{
		auto it = std::remove_if(Components.begin(), Components.end(),
			[](USceneComponent* comp) { return dynamic_cast<T*>(comp) != nullptr; });

		Components.erase(it, Components.end());
	}


protected:
	bool bCanEverTick = false;
	std::unordered_set<std::shared_ptr<USceneComponent>> Components;
};

