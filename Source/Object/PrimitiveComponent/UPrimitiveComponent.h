#pragma once

#include "Core/Engine.h"
#include "Object/USceneComponent.h"
#include "Primitive/PrimitiveVertices.h"
#include "Core/Math/Plane.h"
#include "Core/Rendering/RenderResource.h"

/*
* NOTE : 모든 PrimitiveComponent를 상속받는 개체는 shaderidx, constantbuffer index를 개별 지정해줘야 합니다
*/

class UBillboardUtilComponent;

class UPrimitiveComponent : public USceneComponent, public FRenderResource
{
	using Super = USceneComponent;
public:
	UPrimitiveComponent() {};
	virtual ~UPrimitiveComponent() = default;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void UpdateConstantPicking(const URenderer& Renderer, FVector4 UUIDColor) const;
	void UpdateConstantDepth(const URenderer& Renderer, int Depth) const;
	virtual void Render();
	virtual void UpdateConstantData(URenderer*& Renderer);

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
	bool GetIsOrthoGraphic() { return bIsOrthoGraphic; }

protected:
	bool bCanBeRendered = false;
	bool bUseVertexColor = true;
	bool bIsOrthoGraphic = false;
	FVector4 CustomColor = FVector4(1.0f, 1.0f, 1.0f, 1.0f);
public:
	FRenderResource RenderResource;
	FConstants ConstantData;

public:
	bool IsUseBillboardUtil() const { return bUseBillboardUtil; }
	virtual void SetUseBillboardUtil(bool bUse);

protected:
	bool bUseBillboardUtil = false;
	UBillboardUtilComponent* BillboardUtil = nullptr;
};

class UCubeComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	UCubeComp()
	{
		/*bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColor);*/
		// shader 관련 index 지정 필요
		//

		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColorNormalTex);
		RenderResource.InputLayoutType = InputLayoutType::POSCOLORNORMALTEX;
		RenderResource.VertexShaderIndex = 1;
		RenderResource.PixelShaderIndex = 1;
		RenderResource.bUseIndexBuffer = true;
		RenderResource.ShaderResourceViewIndices.emplace().push_back(0);		// 0번째 Texture 사용 : box2.png [값이 없으면 초기화]
	}
	virtual ~UCubeComp() = default;
	EPrimitiveType GetType() override
	{
		//return EPrimitiveType::EPT_Cube;
		return EPrimitiveType::EPT_CubeTex;
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
		RenderResource.Stride = sizeof(FPosColorNormalTex);
		RenderResource.InputLayoutType = InputLayoutType::POSCOLORNORMALTEX;
		RenderResource.VertexShaderIndex = 1;
		RenderResource.PixelShaderIndex = 1;
		RenderResource.bUseIndexBuffer = true;
		RenderResource.ShaderResourceViewIndices.emplace().push_back(0);		// 0번째 Texture 사용 : box2.png [값이 없으면 초기화]
		// shader 관련 index 지정 필요
		
	}
	virtual ~USphereComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_SphereTex;
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
		RenderResource.Stride = sizeof(FPosColorNormalTex);
		RenderResource.InputLayoutType = InputLayoutType::POSCOLORNORMALTEX;
		RenderResource.VertexShaderIndex = 1;
		RenderResource.PixelShaderIndex = 1;
		RenderResource.bUseIndexBuffer = true;
		//RenderResource.ShaderResourceViewIndices.emplace().push_back(0);		// 0번째 Texture 사용 : box2.png [값이 없으면 초기화]
	}
	virtual ~UTriangleComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_TriangleTex;
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
		RenderResource.Stride = sizeof(FPosColorNormalTex);
		RenderResource.InputLayoutType = InputLayoutType::POSCOLORNORMALTEX;
		RenderResource.VertexShaderIndex = 1;
		RenderResource.PixelShaderIndex = 1;
		RenderResource.bUseIndexBuffer = true;
		RenderResource.ShaderResourceViewIndices.emplace().push_back(0);		// 0번째 Texture 사용 : box2.png [값이 없으면 초기화]
		// shader 관련 index 지정 필요
	}
	virtual ~UCylinderComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_CylinderTex;
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
		RenderResource.Stride = sizeof(FPosColorNormalTex);
		RenderResource.InputLayoutType = InputLayoutType::POSCOLORNORMALTEX;
		RenderResource.VertexShaderIndex = 1;
		RenderResource.PixelShaderIndex = 1;
		RenderResource.bUseIndexBuffer = true;
		RenderResource.ShaderResourceViewIndices.emplace().push_back(0);		// 0번째 Texture 사용 : box2.png [값이 없으면 초기화]
		// shader 관련 index 지정 필요
	}
	virtual ~UConeComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_ConeTex;
	}
};

class UCircleComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	UCircleComp()
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColorNormalTex);
		RenderResource.InputLayoutType = InputLayoutType::POSCOLORNORMALTEX;
		RenderResource.VertexShaderIndex = 1;
		RenderResource.PixelShaderIndex = 1;
		RenderResource.bUseIndexBuffer = true;
		RenderResource.ShaderResourceViewIndices.emplace().push_back(0);		// 0번째 Texture 사용 : box2.png [값이 없으면 초기화]
		// shader 관련 index 지정 필요
	}
	virtual ~UCircleComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_CircleTex;
	}
};

class UBillBoardComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	UBillBoardComp()
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColorNormalTex);
		RenderResource.InputLayoutType = InputLayoutType::POSCOLORNORMALTEX;
		RenderResource.VertexShaderIndex = 1;
		RenderResource.PixelShaderIndex = 1;
		RenderResource.bUseIndexBuffer = true;
		RenderResource.ShaderResourceViewIndices.emplace().push_back(1);		// 1번째 Texture 사용 : tree.png [값이 없으면 초기화]
		// shader 관련 index 지정 필요
		//
	}
	virtual ~UBillBoardComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_BillBoard;
	}

	virtual void SetUseBillboardUtil(bool bUse) override;

	void UpdateConstantData(URenderer*& Renderer) override;
};



class UWorldCharComp : public UPrimitiveComponent 
{
	using Super = UPrimitiveComponent;
public:
	UWorldCharComp() 
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FPosColorNormalTex);
		RenderResource.InputLayoutType = InputLayoutType::POSCOLORNORMALTEX;
		RenderResource.VertexShaderIndex = 2;				// 2 : Atlas Vertex Shader
		RenderResource.PixelShaderIndex = 2;				// 2 : Atlas Pixel Shader		
		RenderResource.VertexConstantIndex = 3;				// 3 : Atlas Vertex Shader Constant Buffer		
		RenderResource.PixelConstantIndex = -1;				// -1 : [No] PS CBuffer		
		RenderResource.bUseIndexBuffer = true;						
		RenderResource.ShaderResourceViewIndices.emplace().push_back(1);	// TextAtlas 추가 필요
	}

	virtual ~UWorldCharComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_WorldText;
	}

private:
	char Character = 'a';

public:
	void SetChar(char InCharacter) { Character = InCharacter; }
	char GetChar() const { return Character; }
	FAtlasConstants AtlasConstantData;

	void UpdateConstantData(URenderer*& Renderer) override;
};

class UWorldGridComp : public UPrimitiveComponent
{
	using Super = UPrimitiveComponent;
public:
	UWorldGridComp()
	{
		bCanBeRendered = true;
		RenderResource.PrimitiveType = GetType();
		RenderResource.Stride = sizeof(FVertexSimple);
		RenderResource.InputLayoutType = InputLayoutType::POSCOLOR;
		RenderResource.VertexShaderIndex = 0;
		RenderResource.PixelShaderIndex = 0;
		RenderResource.VertexConstantIndex = 0;
		RenderResource.PixelConstantIndex = -1;
		RenderResource.bUseIndexBuffer = false;
		//RenderResource.ShaderResourceViewIndices.emplace().push_back(0);	// TextAtlas 추가 필요
	}

	virtual ~UWorldGridComp() = default;
	EPrimitiveType GetType() override
	{
		return EPrimitiveType::EPT_WORLDGRID;
	}

	void UpdateConstantData(URenderer*& Renderer) override;
};