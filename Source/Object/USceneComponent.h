#pragma once
#include "UObject.h"
#include "Core/Math/Vector.h"
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

	FTransform& GetTransform();
	FTransform& GetLocalTransform() { return Transform; }
	bool CanEverTick() const { return bCanEverTick; }
protected:
	FTransform Transform;
	FTransform* Parent = nullptr;
	bool bCanEverTick = true;

private:
	void SetParent(FTransform* NewParent) { Parent = NewParent; }
};