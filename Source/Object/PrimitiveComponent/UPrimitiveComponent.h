#pragma once

#include "Core/Engine.h"
#include "Object/USceneComponent.h"
#include "Primitive/PrimitiveVertices.h"
#include "Core/Math/Plane.h"

#include "Core/Rendering/RenderResource.h"

/* 
* NOTE : 모든 PrimitiveComponent를 상속받는 개체는 shaderidx, constantbuffer index를 개별 지정해줘야 합니다
*/
class UPrimitiveComponent : public USceneComponent, public FRenderResource
{
	using Super = USceneComponent;
public:
	UPrimitiveComponent() { };
	virtual ~UPrimitiveComponent() = default;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void UpdateConstantPicking(const URenderer& Renderer, FVector4 UUIDColor) const;
	void UpdateConstantDepth(const URenderer& Renderer, int Depth) const;
	virtual void Render();
	void UpdateConstantData(URenderer*& Renderer);

	virtual EPrimitiveType GetType() { return EPrimitiveType::EPT_None; }

	bool IsUseVertexColor() const { return bUseVertexColor; }

	void SetCustomColor(const FVector4& InColor)
	{
		CustomColor = InColor; 
		bUseVertexColor = false;
	}

	void SetUseVertexColor(bool bUse)
	{
		bUseVertexColor = bUse;
	}
	const FVector4& GetCustomColor() const { return CustomColor; }

public:
	virtual void RegisterComponentWithWorld(class UWorld* World);

public:
	void SetCanBeRendered(bool bRender) { bCanBeRendered = bRender; }

	void SetIsOrthoGraphic(bool IsOrtho) { bIsOrthoGraphic = IsOrtho; }
	bool GetIsOrthoGraphic() { return bIsOrthoGraphic;}
	
protected:
	bool bCanBeRendered = false;
	bool bUseVertexColor = true;
	bool bIsOrthoGraphic = false;
	FVector4 CustomColor = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
public:
	FRenderResource RenderResource;
	FConstants ConstantData;
};

class UCubeComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	UCubeComp()
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColor);
		// shader 관련 index 지정 필요
		//
	}
	virtual ~UCubeComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Cube;
	}
};

class USphereComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	USphereComp()
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColor);
		// shader 관련 index 지정 필요
		//
	}
	virtual ~USphereComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Sphere;
	}
};

class UTriangleComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	UTriangleComp()
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColor);
		// shader 관련 index 지정 필요
	}
	virtual ~UTriangleComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Triangle;
	}
};

class ULineComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;

public:
	ULineComp()
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColor);
		// shader 관련 index 지정 필요
		// 
	}
	virtual ~ULineComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Line;
	}
};

class UCylinderComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;

public:
	UCylinderComp()
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColor);
		// shader 관련 index 지정 필요
	}
	virtual ~UCylinderComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Cylinder;
	}
};

class UConeComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	UConeComp()
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColor);
		// shader 관련 index 지정 필요
	}
	virtual ~UConeComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Cone;
	}
};

class UCircleComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;

public:
	UCircleComp()
	{
		bCanBeRendered = true;
	}
	virtual ~UCircleComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_Circle;
	}
};