#pragma once
#include "Object/Actor/Actor.h"
#include "Core/Math/Vector.h"


enum class ESelectedAxis : uint8
{
    None,
    X,
    Y,
    Z
};

class AGizmoHandleAxis : public AActor
{
public:
    AGizmoHandleAxis(ESelectedAxis InAxis);

    void SetGizmoTransform(const FTransform& ParentTransform);
    ESelectedAxis GetAxisType() const { return AxisType; }

private:
    ESelectedAxis AxisType;
    UCylinderComp* AxisComponent;
};
