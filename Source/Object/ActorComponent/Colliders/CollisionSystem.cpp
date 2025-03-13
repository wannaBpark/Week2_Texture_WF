#include "CollisionSystem.h";

bool CollisionSystem::LineToLine(const ULineCollider& a, const ULineCollider& b)
{

	return false;
}

bool CollisionSystem::LineToBox(const ULineCollider& a, const UBoxCollider& b)
{
	return false;
}

bool CollisionSystem::LineToSphere(const ULineCollider& a, const USphereCollider& b)
{
	return false;
}

bool CollisionSystem::BoxToBox(const UBoxCollider& a, const UBoxCollider& b)
{
	return false;
}

bool CollisionSystem::BoxToSphere(const UBoxCollider& a, const USphereCollider& b)
{
	return false;
}

bool CollisionSystem::SphereToSphere(const USphereCollider& a, const USphereCollider& b)
{
	return false;
}
