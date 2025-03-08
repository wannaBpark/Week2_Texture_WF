#pragma once
#include "Vector.h"


struct alignas(16) FVector4 : public FVector
{
    using FVector::X;
    using FVector::Y;
    using FVector::Z;

    float W;
    FVector4()
        : FVector(0, 0, 0), W(0)
    {
    }
    FVector4(float InX, float InY, float InZ, float InW)
        : FVector(InX, InY, InZ), W(InW)
    {
    }
};
