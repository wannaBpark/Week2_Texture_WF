#pragma once
#include "Core/HAL/PlatformType.h"
struct FVertexSimple
{
    float X, Y, Z;    // Position
    float R, G, B, A; // Color
};

enum class EPrimitiveType : uint8
{
	EPT_Triangle,
	EPT_Cube,
	EPT_Sphere,
	EPT_Max,
};

extern FVertexSimple CubeVertices[36];
extern FVertexSimple SphereVertices[2400];
extern FVertexSimple TriangleVertices[3];
