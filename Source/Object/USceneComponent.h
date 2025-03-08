#pragma once
#include "UObject.h"
#include "Core/Math/Vector.h"
#include "Core/Math/Transform.h"
#include "Object/ActorComponent/ActorComponent.h"

class USceneComponent : public UActorComponent
{
	using Super = UActorComponent;
public:
	USceneComponent() = default;
	virtual ~USceneComponent() = default;

public:	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	FTransform& GetTransform() { return Transform; }
	bool CanEverTick() const { return bCanEverTick; }

protected:
	FTransform Transform;
	bool bCanEverTick = true;
};