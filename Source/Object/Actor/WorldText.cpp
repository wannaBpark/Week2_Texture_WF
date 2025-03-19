#include "Object/Actor/WorldText.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"
#include "Core/EngineTypes.h"
#include "Static/FEditorManager.h"
#include "Core/Math/Transform.h"
#include "Core/FSceneManager.h"
#include "Debug/DebugConsole.h"
#include "Object/UtilComponent/UStringComponent.h"


AWorldText::AWorldText()
{

	bCanEverTick = true;

	StringComponent = AddComponent<UStringComponent>();
	RootComponent = StringComponent;

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
}

const char* AWorldText::GetTypeName()
{
	return "WorldText";
}


void AWorldText::ClearCharComps()
{
	StringComponent->ClearCharComps();
}

void AWorldText::SetCharComps(std::string InText)
{
	StringComponent->SetCharComps(InText);
}

std::string AWorldText::GetString()
{
	return StringComponent->GetString();
}

float AWorldText::GetLetterSpacing()
{
	return StringComponent->GetLetterSpacing();
}

// !!!!! 현재 코드상 SetTexComp 전에 불러야 함!
void AWorldText::SetLetterSpacing(float InLetterSpacing)
{
	StringComponent->SetLetterSpacing(InLetterSpacing);
}

void AWorldText::SetActive(bool bActive)
{
	bIsActive = bActive;
	StringComponent->SetActive(bActive);
}

void AWorldText::SetUseBillboardUtil(bool bUse)
{
	StringComponent->SetUseBillboardUtil(bUse);
}
