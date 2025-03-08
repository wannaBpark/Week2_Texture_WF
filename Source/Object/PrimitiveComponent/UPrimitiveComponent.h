#pragma once

#include "Core/Engine.h"
#include "Object/USceneComponent.h"
#include "Primitive/PrimitiveVertices.h"


class UPrimitiveComponent : public USceneComponent
{
	using Super = USceneComponent;
public:
	UPrimitiveComponent() = default;
	virtual ~UPrimitiveComponent() = default;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render();

	virtual EPrimitiveType GetType() { return EPrimitiveType::EPT_None; }

protected:
	const bool bCanBeRendered = GetType() != EPrimitiveType::EPT_None;
};

class UCubeComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Cube;
	}
};

class USphereComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Sphere;
	}
};

class UTriangleComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Triangle;
	}
};
