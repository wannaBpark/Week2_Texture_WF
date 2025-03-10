#include "UPrimitiveComponent.h"
#include <Debug/DebugConsole.h>

void UPrimitiveComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPrimitiveComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
}

void UPrimitiveComponent::Render()
{
	URenderer* Renderer = UEngine::Get().GetRenderer();
	if (Renderer == nullptr /*|| !bCanBeRendered*/)
	{
		return;
	}
	Renderer->RenderPrimitive(this, bIsPicked);
}

void UPrimitiveComponent::RegisterComponentWithWorld(UWorld* World)
{
	World->AddRenderComponent(this);
}
