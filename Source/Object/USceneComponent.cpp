#include "USceneComponent.h"
#include "Debug/DebugConsole.h"

void USceneComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USceneComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void USceneComponent::SetTransform(const FTransform& InTransform)
{
	Transform = InTransform;
	UpdateChildrenTransform();
}

void USceneComponent::SetupAttachment(USceneComponent* InParent, bool bUpdateChildTransform)
{
	if (InParent)
	{
		Parent = InParent;
		InParent->Children.Add(this);
		if (bUpdateChildTransform)
		{
			Transform = InParent->GetComponentTransform() * Transform;
		}
	}
	else
	{
		UE_LOG("Parent is nullptr");
	}
}

void USceneComponent::UpdateChildrenTransform()
{
	for (auto& Child : Children)
	{
		FTransform NewTransform = Transform * Child->GetComponentTransform();
		Child->SetTransform(NewTransform);
	}
}
