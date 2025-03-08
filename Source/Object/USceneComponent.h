#pragma once
#include "UObject.h"
#include "Core/Math/Vector.h"
#include "Core/Math/Transform.h"

class USceneComponent : public UObject
{
public:
	FTransform& GetTransform() { return Transform; }
	virtual void Tick(float DeltaTime) {};

protected:
	FTransform Transform;
};