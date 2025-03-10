#include "GizmoHandle.h"

#include "Object/Actor/Camera.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"
#include "Object/World/World.h"
#include "Static/FEditorManager.h"

AGizmoHandle::AGizmoHandle()
{
	bIsGizmo = true;
	// !NOTE : Z방향으로 서있음
	// z
	UCylinderComp* ZArrow = AddComponent<UCylinderComp>();
	ZArrow->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(0.01, 0.01, 0.5)));
	ZArrow->SetCustomColor(FVector4(0.0f, 0.0f, 1.0f, 1.0f));
	CylinderComponents.Add(ZArrow);

	// x
	UCylinderComp* XArrow = AddComponent<UCylinderComp>();
	XArrow->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 90.0f, 0.0f), FVector(1, 1, 1)));
	XArrow->SetCustomColor(FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	CylinderComponents.Add(XArrow);

	// y
	UCylinderComp* YArrow = AddComponent<UCylinderComp>();
	YArrow->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, 0.0f), FVector(90.0f, 0.0f, 0.0f), FVector(1, 1, 1)));
	YArrow->SetCustomColor(FVector4(0.0f, 1.0f, 0.0f, 1.0f));
	CylinderComponents.Add(YArrow);
	RootComponent = ZArrow;
	
	UEngine::Get().GetWorld()->AddZIgnoreComponent(ZArrow);
	UEngine::Get().GetWorld()->AddZIgnoreComponent(XArrow);
	UEngine::Get().GetWorld()->AddZIgnoreComponent(YArrow);

	ZArrow->SetCustomColor(FVector4(0.0f, 1.0f, 0.0f, 1.0f));
	XArrow->SetCustomColor(FVector4(0.0f, 1.0f, 0.0f, 1.0f));
	YArrow->SetCustomColor(FVector4(0.0f, 1.0f, 0.0f, 1.0f));

	XArrow->SetupAttachment(ZArrow, true);
	YArrow->SetupAttachment(ZArrow, true);

	SetActive(false);
}

void AGizmoHandle::Tick(float DeltaTime)
{
	AActor* SelectedActor  = FEditorManager::Get().GetSelectedActor();
	if (SelectedActor != nullptr && bIsActive)
	{
		auto Transform = SelectedActor->GetActorTransform();
		Transform.SetScale(1, 1, 1);
		SetActorTransform(Transform);
	}

	SetScaleByDistance();
	
	AActor::Tick(DeltaTime);
}

void AGizmoHandle::SetScaleByDistance()
{
	FTransform MyTransform = GetActorTransform();
	
	// 액터의 월드 위치
	FVector actorWorldPos = MyTransform.GetPosition();

	FTransform CameraTransform = FEditorManager::Get().GetCamera()->GetActorTransform();
	
	// 카메라의 월드 위치
	FVector cameraWorldPos = CameraTransform.GetPosition();

	// 거리 계산
	float distance = (actorWorldPos - cameraWorldPos).Length();

	float baseScale = 1.0f;    // 기본 스케일
	float scaleFactor = distance * 0.1f; // 거리에 비례하여 스케일 증가

	// float minScale = 1.0f;     // 최소 스케일
	// float maxScale = 1.0f;     // 최대 스케일
	// float scaleFactor = clamp(1.0f / distance, minScale, maxScale);

	MyTransform.SetScale(scaleFactor, scaleFactor, scaleFactor);
}

void AGizmoHandle::SetActive(bool bActive)
{
	bIsActive = bActive;
	for (auto& Cylinder : CylinderComponents)
	{
		Cylinder->SetCanBeRendered(bActive);
	}
}

const char* AGizmoHandle::GetTypeName()
{
	return "GizmoHandle";
}

