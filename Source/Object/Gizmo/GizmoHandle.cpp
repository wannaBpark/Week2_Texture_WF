﻿#include "GizmoHandle.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"


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
	FTransform tr = XArrow->GetComponentTransform();
	tr.Rotate(FVector(0.0f, 90.0f, 0.0f));
	XArrow->SetRelativeTransform(tr);

	XArrow->SetCustomColor(FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	CylinderComponents.Add(XArrow);

	// y
	UCylinderComp* YArrow = AddComponent<UCylinderComp>();
	tr = YArrow->GetComponentTransform();
	tr.Rotate(FVector(90.0f, 0.0f, 0.0f));
	YArrow->SetRelativeTransform(tr);
	YArrow->SetCustomColor(FVector4(0.0f, 1.0f, 0.0f, 1.0f));
	CylinderComponents.Add(YArrow);
	RootComponent = ZArrow;

	XArrow->SetupAttachment(ZArrow);
	YArrow->SetupAttachment(ZArrow);


	SetActive(false);
}

void AGizmoHandle::SetActive(bool bActive)
{
	for (auto& Cylinder : CylinderComponents)
	{
		Cylinder->SetCanBeRendered(bActive);
	}
}

const char* AGizmoHandle::GetTypeName()
{
	return "GizmoHandle";
}

