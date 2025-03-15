#include "Object/Actor/WorldText.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"
#include "Core/EngineTypes.h"

#include "Debug/DebugConsole.h"

AWorldText::AWorldText()
{
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
		
		CharComps[i]->EndPlay(EEndPlayReason::Destroyed);
		CharComps[i]->~UWorldCharComp();
		CharComps.RemoveAt(i);
	}
	CharComps.Empty();
}

void AWorldText::SetCharComps(std::string& InText)
{
	if (CharComps.Num() != 0) 
	{
		ClearCharComps();
	}

	if (InText.size() == 0)
		return;
	float TextSize = static_cast<float>(InText.size());
	float Middle = (TextSize + (TextSize - 1.0f) * LetterSpacing) / 2.0f;
	for (int32 i = 0; i < InText.size(); i++)
	{
		UWorldCharComp* CharComponent = AddComponent<UWorldCharComp>();
		CharComponent->Parent = RootComponent;
		CharComponent->SetRelativeTransform(
			FTransform(FVector(0.f, -Middle + 0.5f + static_cast<float>(i) * (1 + LetterSpacing), 0.f),
				FQuat(0, 0, 0, 1),
				FVector(1, 1, 1)));
		CharComponent->SetChar(InText[i]);
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
