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

const FTransform& USceneComponent::GetWorldTransform()
{
	if (Parent)
	{
		// 내 기준
		FTransform ParentWorldTransform = Parent->GetWorldTransform();
		// 현재 컴포넌트의 상대 Transform을 부모의 월드 Transform과 결합
		FTransform WorldTransform = RelativeTransform.ApplyParentTransform(ParentWorldTransform);

		return WorldTransform;
	}

	return RelativeTransform;
}

void USceneComponent::SetRelativeTransform(const FTransform& InTransform)
{
	RelativeTransform = InTransform;
	UpdateChildrenTransform();
}

void USceneComponent::Pick(bool bPicked)
{
	bIsPicked = bPicked;
}

void USceneComponent::SetupAttachment(USceneComponent* InParent, bool bUpdateChildTransform)
{
	if (InParent)
	{
		Parent = InParent;
		InParent->Children.Add(this);
		if (bUpdateChildTransform)
		{
			FTransform NewRelativeTransform = RelativeTransform.ApplyParentTransform(Parent->GetWorldTransform());
			SetRelativeTransform(NewRelativeTransform);
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
		// 부모의 월드, 자식의 로컬
		FTransform NewChildTransform = Child->RelativeTransform.ApplyParentTransform(GetWorldTransform());
		Child->SetRelativeTransform(NewChildTransform);
	}
}
