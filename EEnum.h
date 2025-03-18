#pragma once
enum class EProjectionType {

};

enum class ECollisionDetection {
	OBB,
	AABB,
};

enum class ESelectedAxis : unsigned int
{
	None,
	X,
	Y,
	Z
};

enum class EGizmoType : unsigned int
{
	Translate,
	Rotate,
	Scale,
	Max
};

struct FHitColliderInfo {
	float minX = { 0 };
	float maxX = { 0 };
	float minY = { 0 };
	float maxY = { 0 };
	float minZ = { 0 };
	float maxZ = { 0 };
};