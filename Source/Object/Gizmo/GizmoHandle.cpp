#include "GizmoHandle.h"
#include "Object/PrimitiveComponent/UPrimitiveComponent.h"


AGizmoHandle::AGizmoHandle()
{
	// !NOTE : X방향으로 누워있음
	// z
	UCylinderComp* ZArrow = AddComponent<UCylinderComp>();
	ZArrow->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(0.03f, 0.03f, 0.5f)));
	ZArrow->SetCustomColor(FVector4(0.0f, 0.0f, 1.0f, 1.0f));
	ArrowComponents.Add(ZArrow);

	// x
	UCylinderComp* XArrow = AddComponent<UCylinderComp>();
	XArrow->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 90.0f, 0.0f), FVector(0.03f, 0.03f, 0.5f)));
	XArrow->SetCustomColor(FVector4(1.0f, 0.0f, 0.0f, 1.0f));
	ArrowComponents.Add(XArrow);

	//
	UCylinderComp* YArrow = AddComponent<UCylinderComp>();
	YArrow->SetRelativeTransform(FTransform(FVector(0.0f, 0.0f, 0.0f), FVector(90.0f, 0.0f, 0.0f), FVector(0.03f, 0.03f, 0.5f)));
	YArrow->SetCustomColor(FVector4(0.0f, 1.0f, 0.0f, 1.0f));
	ArrowComponents.Add(YArrow);

}

const char* AGizmoHandle::GetTypeName()
{
	return "GizmoHandle";
}

