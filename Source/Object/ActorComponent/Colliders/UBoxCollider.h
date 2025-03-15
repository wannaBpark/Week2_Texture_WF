#pragma once
#include "ICollider.h"
#include "Object/ActorComponent/Colliders/CollisionSystem.h";
#include "Core/Math/Transform.h"

class UBoxCollider : public ICollider
{
public:
	bool CheckCollision(const ICollider& other) const override {
		return other.CheckCollision(*this);
	}

	virtual bool CheckCollision(const class ULineCollider& line) const {
		return CollisionSystem::LineToBox(line, *this);
	}
	virtual bool CheckCollision(const class UBoxCollider& box) const {
		return CollisionSystem::BoxToBox(*this, box);
	}
	virtual bool CheckCollision(const class USphereCollider& sphere) const {
		return CollisionSystem::BoxToSphere(*this, sphere);
	}
private:
	FTransform relativeTransform;
};

