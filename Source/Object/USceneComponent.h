#pragma once
#include "UObject.h"
#include "Core/Math/Vector.h"
#include "Core/Container/Set.h"
#include "Core/Math/Transform.h"
#include "Object/ActorComponent/ActorComponent.h"

class USceneComponent : public UActorComponent
{
	friend class AActor;
	using Super = UActorComponent;
public:
	USceneComponent() = default;
	virtual ~USceneComponent() = default;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	/* 로컬 트랜스폼을 반환*/
	const FTransform& GetComponentTransform() { return RelativeTransform; }
	/* 월드 트랜스폼을 반환*/
	const FTransform& GetWorldTransform();

	void SetRelativeTransform(const FTransform& InTransform);
	bool CanEverTick() const { return bCanEverTick; }

	void Pick(bool bPicked);

public:
	void SetupAttachment(USceneComponent* InParent, bool bUpdateChildTransform = false);

protected:
	void UpdateChildrenTransform();

protected:
	USceneComponent* Parent = nullptr;
	TSet<USceneComponent*> Children;
	FTransform RelativeTransform = FTransform();
	bool bCanEverTick = true;

	// debug
protected:
	bool bIsPicked = false;
};