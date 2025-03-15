#include "FEditorManager.h"
#include "Core/Engine.h"
#include "Object/World/World.h"
#include "Object/Gizmo/GizmoHandle.h"
#include "Core/Math/Vector.h"
#include "Core/Math/Transform.h"

void FEditorManager::SelectActor(AActor* NewActor)
{
    if (GizmoHandle == nullptr)
    {
		GizmoHandle = UEngine::Get().GetWorld()->SpawnActor<AGizmoHandle>();
    	GizmoHandle->SetDepth(1);
        GizmoHandle->SetActive(false);
    }

    if (BoundingBoxComp == nullptr) {
        BoundingBoxComp = NewActor->AddComponent<UBoundingBoxComp>();
        BoundingBoxComp->RegisterComponentWithWorld(UEngine::Get().GetWorld());

    }

	if (SelectedActor == NewActor)
		return;
	
    if (SelectedActor != nullptr && SelectedActor != NewActor)
    {
        SelectedActor->UnPick();
        GizmoHandle->SetActive(false);
        BoundingBoxComp->SetCanBeRendered(false);
    }

	SelectedActor = NewActor;
	
    if (SelectedActor != nullptr)
    {
        BoundingBoxComp->SetupAttachment(SelectedActor->GetRootComponent());
        SelectedActor->Pick();
        GizmoHandle->SetActive(true);
        BoundingBoxComp->SetCanBeRendered(true);
        //FVector Pos = SelectedActor->GetActorTransform().GetPosition();
		//FTransform GizmoTransform = GizmoHandle->GetActorTransform();
		//GizmoTransform.SetPosition(Pos);
		//GizmoHandle->SetActorTransform(GizmoTransform);
        //GizmoHandle
	}
}

void FEditorManager::SetCamera(ACamera* NewCamera)
{
    Camera = NewCamera;
}
