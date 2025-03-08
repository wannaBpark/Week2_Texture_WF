#include "UPrimitiveComponent.h"

void UPrimitiveComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPrimitiveComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Render();
}

void UPrimitiveComponent::Render()
{
	URenderer* Renderer = UEngine::Get().GetRenderer();
	if (Renderer == nullptr || bCanBeRendered)
	{
		return;
	}

	Renderer->RenderPrimitive(this);
}
