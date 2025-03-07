#pragma once
#include "Vector.h"


struct alignas(16) FPlane : public FVector
{
    using FVector::X;
    using FVector::Y;
    using FVector::Z;

    float W;
    FPlane()
        : FVector(0, 0, 0), W(0)
    {
    }
    FPlane(float InX, float InY, float InZ, float InW)
        : FVector(InX, InY, InZ), W(InW)
    {
    }
};
