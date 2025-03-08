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
		size_t ObjectSize = sizeof(T);
		FPlatformMemory::IncrementStats(ObjectSize);

		std::shared_ptr<T> NewObject(new T, [&](T* obj) {
			FPlatformMemory::DecrementStats(ObjectSize);
			});

		return NewObject;
	}
};

