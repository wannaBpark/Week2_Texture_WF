#pragma once
#include "ICollider.h"
#include "Object/ActorComponent/Colliders/CollisionSystem.h";

class USphereCollider : public ICollider
{
	bool CheckCollision(const ICollider& other) const override {
		return other.CheckCollision(*this);
	}

	virtual bool CheckCollision(const class ULineCollider& line) const {
		return CollisionSystem::LineToSphere(line, *this);
	}
	virtual bool CheckCollision(const class UBoxCollider& box) const {
		return CollisionSystem::BoxToSphere(box, *this);
	}
	virtual bool CheckCollision(const class USphereCollider& sphere) const {
		return CollisionSystem::SphereToSphere(*this, sphere);
	}
};

