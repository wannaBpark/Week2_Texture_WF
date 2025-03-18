#include "Object/Actor/WorldText.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"
#include "Core/EngineTypes.h"
#include "Static/FEditorManager.h"
#include "Core/Math/Transform.h"

#include "Debug/DebugConsole.h"

#include "Object/UClassManager.h"

AWorldText::AWorldText()
{
	EquipUClass(AWorldText, ClassType);

	bCanEverTick = true;

	USceneComponent* SceneComponent = AddComponent<USceneComponent>();
	RootComponent = SceneComponent;

}

void AWorldText::BeginPlay()
{
	Super::BeginPlay();
}

void AWorldText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AActor* SelectedActor = FEditorManager::Get().GetSelectedActor();

	if (SelectedActor != nullptr && bIsActive)
	{
		FTransform RootTr = SelectedActor->GetRootComponent()->GetRelativeTransform();
		RootTr.Translate(FVector(0, 0, 1));
		SetActorTransform(RootTr); 
	}

	int32 num = CharComps.Num();
	for (int32 i = 0; i < num; i++)
	{
		CharComps[i].Render();
	}

}

const char* AWorldText::GetTypeName()
{
	return "WorldText";
}

void AWorldText::ClearCharComps()
{
	int32 num = CharComps.Num();
	for (int32 i = 0; i < num; i++) 
	{
		CharComps[i].EndPlay(EEndPlayReason::Destroyed);
	}
	CharComps.Empty();
}

void AWorldText::SetCharComps(std::string InText)
{
	if (CharComps.Num() == InText.size()) {
		for (int i = 0; i < CharComps.Num(); i++) {
			CharComps[i].SetChar(InText[i]);
		}
		return;
	}

	ClearCharComps();

	if (InText.size() == 0)
		return;
	float TextSize = static_cast<float>(InText.size());
	float Middle = (TextSize + (TextSize - 1.0f) * LetterSpacing) / 2.0f;
	for (int32 i = 0; i < InText.size(); i++)
	{
		UWorldCharComp CharComponent = UWorldCharComp();
		CharComponent.SetupAttachment(RootComponent);
		CharComponent.SetOwner(this);
		CharComponent.SetRelativeTransform(
			FTransform(FVector(0.f, -Middle + 0.5f + static_cast<float>(i) * (1 + LetterSpacing), 0.f),
				FQuat(0, 0, 0, 1),
				FVector(1, 1, 1)));
		CharComponent.SetChar(InText[i]);
		CharComps.Add(CharComponent);
	}
}

float AWorldText::GetLetterSpacing()
{
	return LetterSpacing;
}

// !!!!! 현재 코드상 SetTexComp 전에 불러야 함!
void AWorldText::SetLetterSpacing(float InLetterSpacing)
{
	LetterSpacing = InLetterSpacing;
}

void AWorldText::SetActive(bool bActive)
{
	bIsActive = bActive;
	for (int32 i = 0; i < CharComps.Num(); i++)
	{
		CharComps[i].SetCanBeRendered(bIsActive);
	}
}

void AWorldText::SetUseBillboardUtil(bool bUse)
{
	bUseBillboardUtil = bUse;
	for (int32 i = 0; i < CharComps.Num(); i++)
	{
		CharComps[i].SetUseBillboardUtil(bUse);
	}
}

UClass* AWorldText::GetClass()
{
	return UClassManager::Get().GetClass<AWorldText>();
}
