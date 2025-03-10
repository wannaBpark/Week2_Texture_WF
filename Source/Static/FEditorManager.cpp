#include "FEditorManager.h"
#include "Core/Engine.h"
#include "Object/World/World.h"
#include "Object/Gizmo/GizmoHandle.h"

void FEditorManager::SelectActor(AActor* NewActor)
{
    if (GizmoHandle == nullptr)
    {
		GizmoHandle = UEngine::Get().GetWorld()->SpawnActor<AGizmoHandle>();
    }

    if (SelectedActor != nullptr)
    {
        SelectedActor->UnPick();
		GizmoHandle->SetActive(false);
    }
    SelectedActor = NewActor;

    if (NewActor != nullptr)
    {
        SelectedActor->Pick();
        GizmoHandle->SetActive(true);
		GizmoHandle->SetActorTransform(SelectedActor->GetActorTransform());
        // Gizmos.SelectedActor = NewActor;
    }
}
