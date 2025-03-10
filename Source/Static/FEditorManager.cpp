#include "FEditorManager.h"

void FEditorManager::SelectActor(AActor* NewActor)
{
    if (SelectedActor != nullptr)
    {
        SelectedActor->UnPick();
        // Gizmos.SelectedActor = nullptr;
    }
    SelectedActor = NewActor;

    if (NewActor != nullptr)
    {
        SelectedActor->Pick();
        // Gizmos.SelectedActor = NewActor;
    }
}
