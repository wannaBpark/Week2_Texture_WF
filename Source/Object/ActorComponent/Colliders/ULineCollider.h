#pragma once
#include "ICollider.h"
#include "Object/ActorComponent/Colliders/CollisionSystem.h";

class ULineCollider : public ICollider
{
	bool CheckCollision(const ICollider& other) const override {
		return other.CheckCollision(*this);
	}
	
	virtual bool CheckCollision(const class ULineCollider& line) const {
		return CollisionSystem::LineToLine(*this, line);
	}
	virtual bool CheckCollision(const class UBoxCollider& box) const {
		return CollisionSystem::LineToBox(*this, box);
	}
	virtual bool CheckCollision(const class USphereCollider& sphere) const {
		return CollisionSystem::LineToSphere(*this, sphere);
	}
};

