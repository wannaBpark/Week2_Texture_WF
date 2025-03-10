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
        GizmoHandle->SetActive(false);
    }

    if (NewActor == nullptr)
        return;

    if (SelectedActor != nullptr)
    {
        SelectedActor->UnPick();
        GizmoHandle->SetActive(false);
    }

    if (NewActor == SelectedActor)
    {
        SelectedActor = nullptr;
    }
    else
    {
        SelectedActor = NewActor;
    }

    if (SelectedActor != nullptr)
    {
        SelectedActor->Pick();
        GizmoHandle->SetActive(true);
        FVector Pos = SelectedActor->GetActorTransform().GetPosition();
		FTransform GizmoTransform = GizmoHandle->GetActorTransform();
		GizmoTransform.SetPosition(Pos);
		GizmoHandle->SetActorTransform(GizmoTransform);
	}
}
