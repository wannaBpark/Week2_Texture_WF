#pragma once

#include "Core/Engine.h"
#include "Object/USceneComponent.h"
#include "Primitive/PrimitiveVertices.h"


class UPrimitiveComponent : public USceneComponent
{
	using Super = USceneComponent;
public:
	virtual void Tick(float DeltaTime) override
	{
		Super::Tick(DeltaTime);

		Render();
	}

	virtual void Render()
	{
		URenderer* Renderer = UEngine::Get().GetRenderer();
		if (Renderer == nullptr || !bCanBeRendered)
		{
			return;
		}

		Renderer->RenderPrimitive(PrimitiveType);
	}

protected:
	EPrimitiveType PrimitiveType = EPrimitiveType::EPT_None;
	bool bCanBeRendered = PrimitiveType != EPrimitiveType::EPT_None;
};

class UCubeComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
	virtual void Render() override
	{
		Super::Render();
	}

protected:
	EPrimitiveType PrimitiveType = EPrimitiveType::EPT_Cube;
};

class USphereComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
	virtual void Render() override
	{
		Super::Render();
	}

protected:
	EPrimitiveType PrimitiveType = EPrimitiveType::EPT_Sphere;
};