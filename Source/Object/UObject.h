#pragma once
#include <memory>

#include "NameTypes.h"
#include "Core/Container/String.h"
#include "Core/HAL/PlatformType.h"


// TODO: RTTI 구현하면 enable_shared_from_this 제거
class UObject : public std::enable_shared_from_this<UObject>
{
	friend class FObjectFactory; // 새 오브젝트 생성시 FName 변경 권한 위해 (UClass도 friend 필요 가능성)

	uint32 UUID = 0;
	uint32 InternalIndex = -1; // Index of GUObjectArray

	/* Object의 Instance 이름 */
	// TODO : UClass 및 RTTI 관련 세팅 : static 인스턴스 및 IsA 세팅, 매크로 연결, SceneManager상의 GUObjects의 인덱싱 갱신
	FName Name;	

public:
	UObject();
	virtual ~UObject();

public:
	FName GetFName() const noexcept { return Name; }
	FString GetName() const { return GetFName().ToString(); }

	uint32 GetUUID() const { return UUID; }
	uint32 GetInternalIndex() const { return InternalIndex; }
};