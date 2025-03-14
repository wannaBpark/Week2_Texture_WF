#include "UPrimitiveComponent.h"
#include "Object/World/World.h"
#include "Object/Actor/Actor.h"


void UPrimitiveComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPrimitiveComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void UPrimitiveComponent::UpdateConstantPicking(const URenderer& Renderer, const FVector4 UUIDColor)const
{
	Renderer.UpdateConstantPicking(UUIDColor);
}

void UPrimitiveComponent::UpdateConstantDepth(const URenderer& Renderer, const int Depth)const
{
	Renderer.UpdateConstantDepth(Depth);
}

void UPrimitiveComponent::Render() // 오버라이딩 필요
{
	URenderer* Renderer = UEngine::Get().GetRenderer();
	if (Renderer == nullptr || !bCanBeRendered)
	{
		return;
	}
	if (GetOwner()->IsGizmoActor() == false)
	{
		if (bIsPicked)
		{
			/*bUseVertexColor = false;
			SetCustomColor(FVector4(1.0f, 0.647f, 0.0f, 1.0f));*/
		}
		else
		{
			bUseVertexColor = true;
		}
	}
	//Renderer->RenderPrimitive(this); // 실제 렌더링 요청 수행
	
	this->UpdateConstantData(Renderer);
	Renderer->RenderPrimitive(this, this->RenderResource);
}

void UPrimitiveComponent::RegisterComponentWithWorld(UWorld* World)
{
	World->AddRenderComponent(this);
}

void UPrimitiveComponent::UpdateConstantData(URenderer*& Renderer)
{
	/*ConstantUpdateInfo UpdateInfo{
		this->GetComponentTransform(),
		this->GetCustomColor(),
		this->IsUseVertexColor()
	};*/

	ConstantUpdateInfo UpdateInfo{
		this->GetComponentTransformMatrix(),
		this->GetCustomColor(),
		this->IsUseVertexColor()
	};

	// 업데이트할 자료형들
	FMatrix MVP = FMatrix::Transpose(Renderer->GetProjectionMatrix())
		* FMatrix::Transpose(Renderer->GetViewMatrix())
		* FMatrix::Transpose(UpdateInfo.TransformMatrix);


	ConstantData.MVP = MVP;
	ConstantData.Color = UpdateInfo.Color;
	ConstantData.bUseVertexColor = UpdateInfo.bUseVertexColor;
	

	Renderer->UpdateBuffer(ConstantData, RenderResource.VertexConstantIndex);
	//Renderer->UpdateBuffer(ConstantData, RenderResource.PixelConstantIndex);		// 픽셀 상수 버퍼 업데이트 시 
}
