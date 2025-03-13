#include "UBoxCollider.h"
#include "Object/Actor/Actor.h"

FVector UBoxCollider::GetCenter() const
{
    return GetOwner()->GetActorTransform().GetPosition() + offset;
}
