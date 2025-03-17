#include "UPrimitiveComponent.h"
#include "Object/World/World.h"
#include "Object/Actor/Actor.h"
#include "../Source/Static/FEditorManager.h"
#include "Object/Actor/Camera.h"
#include "Core/Rendering/TextAtlasManager.h"
#include "Core/Rendering/SubUVManager.h"
#include "Core/Math/Vector.h"

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
	FVector4 indexColor = APicker::EncodeUUID(this->GetUUID());
	indexColor /= 255.0f;
	if (GetOwner()->IsGizmoActor() == false)
	{
		if (GetOwner()== FEditorManager::Get().GetSelectedActor())
		{
			bIsPicked = true;
			//UE_LOG("ispicked ");
		}
		else
		{
			bIsPicked = false;
			//UE_LOG("bisunpicked ");
		}		
	}
	FConstants UpdateInfo{
		this->GetComponentTransformMatrix(),
		this->GetCustomColor(),
		(uint32)this->IsUseVertexColor(),
		FEditorManager::Get().GetCamera()->GetActorTransform().GetPosition(),
		indexColor,
		(uint32)this->IsPicked(),
		FEditorManager::Get().GetCamera()->GetActorTransform().GetPosition(),
	};
	FMatrix& WorldPosition = UpdateInfo.MVP;
	// 업데이트할 자료형들
	FMatrix MVP = FMatrix::Transpose(Renderer->GetProjectionMatrix())
		* FMatrix::Transpose(Renderer->GetViewMatrix())
		* FMatrix::Transpose(WorldPosition);


	ConstantData = {
		MVP, UpdateInfo.Color,
		UpdateInfo.bUseVertexColor,
		UpdateInfo.eyeWorldPos,
		UpdateInfo.indexColor,
		UpdateInfo.bIsPicked,
		UpdateInfo.Padding,
	};
	

	Renderer->UpdateBuffer(ConstantData, RenderResource.VertexConstantIndex);
	Renderer->UpdateBuffer(ConstantData, RenderResource.PixelConstantIndex);		// 픽셀 상수 버퍼 업데이트 시 
}

void UBillBoardComp::UpdateConstantData(URenderer*& Renderer)
{
	ConstantUpdateInfo UpdateInfo{
		this->GetComponentTransformMatrix(),
		this->GetCustomColor(),
		this->IsUseVertexColor()
	};

	// 카메라와 빌보드 위치 계산
	ACamera* camera = FEditorManager::Get().GetCamera();
	FVector billboardToEye = camera->GetActorTransform().GetPosition() - this->GetComponentTransform().GetPosition();
	billboardToEye.Normalize();

	// 카메라의 오른쪽, Up 벡터 계산
	FVector upVector = camera->GetActorTransform().GetLocalUp();
	FVector rightVector = FVector::CrossProduct(upVector, billboardToEye);
	upVector.Normalize();
	rightVector.Normalize();


	FVector adjustedUp = FVector::CrossProduct(billboardToEye, rightVector);
	adjustedUp.Normalize();

	// 빌보드 회전 행렬 생성
	FMatrix BillboardRotation = FMatrix(
		{ billboardToEye.X, billboardToEye.Y, billboardToEye.Z, 0.0f },
		{ rightVector.X,    rightVector.Y,    rightVector.Z,    0.0f },
		{ adjustedUp.X,     adjustedUp.Y,     adjustedUp.Z,     0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	);

	// 빌보드 위치를 고려한 최종 변환 행렬
	FMatrix BillBoardTransform = this->GetComponentTransformMatrix() * BillboardRotation;

	// MVP 행렬 생성 (뷰 행렬을 Renderer에서 가져옴)
	FMatrix MVP = FMatrix::Transpose(Renderer->GetProjectionMatrix())
		* FMatrix::Transpose(Renderer->GetViewMatrix())   // 기존의 View Matrix를 사용
		* FMatrix::Transpose(BillBoardTransform);         // 빌보드 변환 적용

	// 상수 버퍼 업데이트
	ConstantData.MVP = MVP;
	ConstantData.Color = UpdateInfo.Color;
	ConstantData.bUseVertexColor = UpdateInfo.bUseVertexColor;

	Renderer->UpdateBuffer(ConstantData, RenderResource.VertexConstantIndex);
}

// 박녕준 천재

void UWorldGridComp::UpdateConstantData(URenderer*& Renderer)
{
	FVector4 indexColor = APicker::EncodeUUID(this->GetUUID());
	indexColor /= 255.0f;
	FVector cameraPos = FEditorManager::Get().GetCamera()->GetActorTransform().GetPosition();
	ConstantUpdateInfo UpdateInfo{
		this->GetComponentTransformMatrix(),
		this->GetCustomColor(),
		(uint32)this->IsUseVertexColor(),
		FEditorManager::Get().GetCamera()->GetActorTransform().GetPosition(),
		indexColor
	};

	// 업데이트할 자료형들
	FMatrix MVP = FMatrix::Transpose(Renderer->GetProjectionMatrix())
		* FMatrix::Transpose(Renderer->GetViewMatrix())
		* FMatrix::Transpose(UpdateInfo.WorldPosition);


	ConstantData = {
		MVP, UpdateInfo.Color,
		UpdateInfo.bUseVertexColor,
		UpdateInfo.eyeWorldPos,
		UpdateInfo.indexColor,
	};

	Renderer->UpdateBuffer(ConstantData, RenderResource.VertexConstantIndex);
}
void UWorldCharComp::UpdateConstantData(URenderer*& Renderer)
{
	FVector4 SzOffset;
	SzOffset = UTextAtlasManager::GetCharUV(this->GetChar());
	FAtlasConstants UpdateInfo{
		this->GetComponentTransformMatrix(),
		SzOffset,
	};
	// 업데이트할 자료형들
	FMatrix MVP = FMatrix::Transpose(Renderer->GetProjectionMatrix())
		* FMatrix::Transpose(Renderer->GetViewMatrix())
		* FMatrix::Transpose(this->GetComponentTransformMatrix());

	AtlasConstantData = { MVP, UpdateInfo.AtlasSzOffset };
	Renderer->UpdateBuffer(AtlasConstantData, RenderResource.VertexConstantIndex);
}

void USubUVComponent::UpdateConstantData(URenderer*& Renderer)   // 빌보드도 추가
{
	FVector4 SzOffset;
	SzOffset = USubUVManager::GetFrameUV(this->GetFrame());
	FAtlasConstants UpdateInfo{
		this->GetComponentTransformMatrix(),
		SzOffset,
	};
	// 업데이트할 자료형들
	FMatrix MVP = FMatrix::Transpose(Renderer->GetProjectionMatrix())
		* FMatrix::Transpose(Renderer->GetViewMatrix())
		* FMatrix::Transpose(this->GetComponentTransformMatrix());

	AtlasConstantData = { MVP, UpdateInfo.AtlasSzOffset };
	Renderer->UpdateBuffer(AtlasConstantData, RenderResource.VertexConstantIndex);
}
