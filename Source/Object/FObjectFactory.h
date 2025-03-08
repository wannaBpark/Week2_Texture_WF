#pragma once
#include "UObject.h"
#include "Core/HAL/PlatformMemory.h"
#include "Core/Engine.h"

class FObjectFactory
{
public:
	template<typename T>
		requires std::derived_from<T, UObject>
	static T* ConstructObject()
	{
		constexpr size_t ObjectSize = sizeof(T);
		void* RawMemory = FPlatformMemory::Malloc(ObjectSize);

		T* ObjectPtr = new (RawMemory) T();
		std::shared_ptr<T> NewObject(ObjectPtr, [ObjectSize](T* Obj)
		{
			Obj->~T();
			FPlatformMemory::Free(Obj, ObjectSize);
			UEngine::Get().GObjects.Remove(Obj->shared_from_this());
		});

		UEngine::Get().GObjects.Add(NewObject);
		return NewObject.get();
	}

	template<typename T>
		requires std::derived_from<T, AActor>
	static T* ConstructActor()
	{
		auto Actor = ConstructObject<T>();
		UWorld* World = UEngine::Get().GetWorld();

		if (World == nullptr)
		{
			return nullptr;
		}

		Actor->SetWorld(UEngine::Get().GetWorld());

		World->AddActor(Actor);
		return Actor;
	}

};

