#pragma once
#include "UObject.h"
#include "Core/Math/Vector.h"
#include "Core/Math/Transform.h"

class USceneComponent : public UObject
{
public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

	FTransform& GetTransform() { return Transform; }
	bool CanEverTick() const { return bCanEverTick; }

protected:
	FTransform Transform;
	bool bCanEverTick = false;
};