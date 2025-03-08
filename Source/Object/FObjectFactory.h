#pragma once
#include <memory>
#include "UObject.h"
#include "Core/HAL/PlatformMemory.h"


class FObjectFactory
{
public:
	template<typename T>
		requires std::derived_from<T, UObject>
	static std::shared_ptr<T> ConstructObject()
	{
		constexpr size_t ObjectSize = sizeof(T);
		void* RawMemory = FPlatformMemory::Malloc(ObjectSize);

		T* ObjectPtr = new (RawMemory) T();
		std::shared_ptr<T> NewObject(ObjectPtr, [ObjectSize](T* Obj)
		{
			Obj->~T();
			FPlatformMemory::Free(Obj, ObjectSize);
		});

		return NewObject;
	}
};

