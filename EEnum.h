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