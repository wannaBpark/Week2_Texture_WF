#pragma once
#include <memory>
#include "Core/HAL/PlatformType.h"

class UClass;

// TODO: RTTI 구현하면 enable_shared_from_this 제거
class UObject : public std::enable_shared_from_this<UObject>
{
	friend class FObjectFactory;

	uint32 UUID = 0;
	uint32 InternalIndex; // Index of GUObjectArray

public:
	static UClass* GetClass();

public:
	UObject();
	virtual ~UObject();

public:
	uint32 GetUUID() const { return UUID; }
	uint32 GetInternalIndex() const { return InternalIndex; }

protected:
	UClass* ClassType;

public:
	bool IsA(UClass* OtherClass);
};