#pragma once
#include "Core/Math/Vector.h";
#include "Object/ActorComponent/ActorComponent.h"

class ICollider : UActorComponent
{
public:
	virtual ~ICollider() = default;

	virtual bool CheckCollision(const ICollider& other) const = 0;
	virtual bool CheckCollision(const class ULineCollider& line) const = 0;
	virtual bool CheckCollision(const class UBoxCollider& box) const = 0;
	virtual bool CheckCollision(const class USphereCollider& sphere) const = 0;

private:
	bool bIsTrigger = false;
};

