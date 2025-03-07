#pragma once

struct FVertexSimple
{
    float X, Y, Z;    // Position
    float R, G, B, A; // Color
};

extern FVertexSimple CubeVertices[36];
extern FVertexSimple SphereVertices[2400];
extern FVertexSimple TriangleVertices[3];
